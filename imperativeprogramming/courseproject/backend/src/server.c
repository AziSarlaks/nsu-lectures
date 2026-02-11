#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <ifaddrs.h>
#include <netdb.h>
#include "config.h"
#include "proc_parser.h"
#include "json_formatter.h"

static int server_socket = -1;
static pthread_t update_thread;
static volatile int running = 1;
static pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;
static char system_json[65536];
static CPUStats cpu_prev, cpu_curr;
static CPUStats cores_prev[MAX_CORES], cores_curr[MAX_CORES];
static int cores_count = 0;

void calculate_cpu_usage(CPUStats *prev, CPUStats *curr) {
    if (!prev || !curr) return;
    
    double total_diff = curr->total - prev->total;
    double idle_diff = curr->idle - prev->idle;
    
    if (total_diff > 0) {
        curr->usage_percent = 100.0 * (1.0 - (idle_diff / total_diff));
        if (curr->usage_percent < 0) curr->usage_percent = 0;
        if (curr->usage_percent > 100) curr->usage_percent = 100;
    } else {
        curr->usage_percent = 0.0;
    }
}

void *update_data_thread(void *arg) {
    (void)arg; // Неиспользуемый параметр
    
    MemoryInfo mem;
    ProcessInfo processes[MAX_PROCESSES];
    int process_count = 0;
    
    srand(time(NULL));
    
    // Первоначальное чтение данных
    if (read_cpu_stats(&cpu_prev, cores_prev, &cores_count) != 0) {
        // Значения по умолчанию
        cores_count = 4;
        cpu_prev.total = 1000;
        cpu_prev.idle = 800;
        for (int i = 0; i < cores_count; i++) {
            cores_prev[i].total = 250;
            cores_prev[i].idle = 200;
        }
    }
    
    memcpy(&cpu_curr, &cpu_prev, sizeof(CPUStats));
    for (int i = 0; i < cores_count; i++) {
        memcpy(&cores_curr[i], &cores_prev[i], sizeof(CPUStats));
    }
    
    while (running) {
        usleep(UPDATE_INTERVAL_MS * 1000);
        
        // Чтение текущих данных
        read_cpu_stats(&cpu_curr, cores_curr, &cores_count);
        read_memory_info(&mem);
        get_processes(processes, &process_count);
        
        // Расчет использования CPU
        calculate_cpu_usage(&cpu_prev, &cpu_curr);
        for (int i = 0; i < cores_count; i++) {
            calculate_cpu_usage(&cores_prev[i], &cores_curr[i]);
        }
        
        // Обновление JSON
        pthread_mutex_lock(&data_mutex);
        format_system_info_json(system_json, sizeof(system_json),
                               &cpu_curr, cores_curr, cores_count,
                               &mem, processes, process_count);
        pthread_mutex_unlock(&data_mutex);
        
        // Сохранение для следующей итерации
        memcpy(&cpu_prev, &cpu_curr, sizeof(CPUStats));
        for (int i = 0; i < cores_count; i++) {
            memcpy(&cores_prev[i], &cores_curr[i], sizeof(CPUStats));
        }
    }
    
    return NULL;
}

void send_http_response(int client_socket, int status, const char* content_type, const char* body) {
    char response[4096];
    int length = snprintf(response, sizeof(response),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
        "Access-Control-Allow-Headers: Content-Type\r\n"
        "Content-Length: %ld\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        status,
        status == 200 ? "OK" : "Not Found",
        content_type,
        strlen(body),
        body);
    
    send(client_socket, response, length, 0);
}

void handle_client(int client_socket) {
    char request[4096];
    char method[16], path[256];
    
    // Читаем запрос
    int bytes_read = recv(client_socket, request, sizeof(request) - 1, 0);
    if (bytes_read <= 0) {
        close(client_socket);
        return;
    }
    request[bytes_read] = '\0';
    
    // Парсим метод и путь
    sscanf(request, "%s %s", method, path);
    
    printf("Request: %s %s\n", method, path);
    
    if (strcmp(method, "GET") == 0) {
        if (strcmp(path, "/") == 0 || strcmp(path, "/index.html") == 0) {
            // Отдаем HTML
            const char* html = 
                "<!DOCTYPE html>\n"
                "<html>\n"
                "<head>\n"
                "    <title>System Monitor</title>\n"
                "    <style>\n"
                "        body { font-family: Arial, sans-serif; margin: 40px; }\n"
                "        .container { max-width: 800px; margin: 0 auto; }\n"
                "        .status { padding: 10px; background: #f0f0f0; border-radius: 5px; }\n"
                "        .online { color: green; }\n"
                "        .data { background: #f9f9f9; padding: 20px; margin-top: 20px; border-radius: 5px; }\n"
                "    </style>\n"
                "</head>\n"
                "<body>\n"
                "    <div class=\"container\">\n"
                "        <h1>System Monitor Server</h1>\n"
                "        <div class=\"status\">\n"
                "            <p class=\"online\">✅ Server is running!</p>\n"
                "            <p>API: <a href=\"/api/system\">/api/system</a></p>\n"
                "            <p>Open the frontend at: <code>frontend/index.html</code></p>\n"
                "        </div>\n"
                "        <div class=\"data\">\n"
                "            <h3>Available endpoints:</h3>\n"
                "            <ul>\n"
                "                <li><a href=\"/api/system\">GET /api/system</a> - System information</li>\n"
                "                <li><a href=\"/api/health\">GET /api/health</a> - Health check</li>\n"
                "            </ul>\n"
                "        </div>\n"
                "    </div>\n"
                "</body>\n"
                "</html>";
            
            send_http_response(client_socket, 200, "text/html", html);
            
        } else if (strcmp(path, "/api/system") == 0) {
            // Отдаем JSON с системной информацией
            pthread_mutex_lock(&data_mutex);
            send_http_response(client_socket, 200, "application/json", system_json);
            pthread_mutex_unlock(&data_mutex);
            
        } else if (strcmp(path, "/api/health") == 0) {
            // Health check endpoint
            char buffer[256];
            snprintf(buffer, sizeof(buffer), 
                     "{\"status\":\"ok\",\"service\":\"system-monitor\",\"timestamp\":%ld}",
                     (long)time(NULL));
            send_http_response(client_socket, 200, "application/json", buffer);
            
        } else {
            // 404 Not Found
            const char* not_found = 
                "<html><body><h1>404 Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";
            send_http_response(client_socket, 404, "text/html", not_found);
        }
        
    } else if (strcmp(method, "OPTIONS") == 0) {
        // Preflight request for CORS
        char response[512];
        int length = snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "Access-Control-Allow-Origin: *\r\n"
            "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
            "Access-Control-Allow-Headers: Content-Type\r\n"
            "Content-Length: 0\r\n"
            "\r\n");
        
        send(client_socket, response, length, 0);
        
    } else {
        // Метод не поддерживается
        const char* not_allowed = 
            "<html><body><h1>405 Method Not Allowed</h1></body></html>";
        send_http_response(client_socket, 405, "text/html", not_allowed);
    }
    
    close(client_socket);
}

// Функция для получения локального IP
char* get_local_ip() {
    static char ip[INET_ADDRSTRLEN] = "127.0.0.1";
    struct ifaddrs *ifaddr, *ifa;
    int family;
    
    if (getifaddrs(&ifaddr) == -1) {
        return ip;
    }
    
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) continue;
        
        family = ifa->ifa_addr->sa_family;
        
        // Проверяем IPv4 и не петлевой интерфейс
        if (family == AF_INET && strcmp(ifa->ifa_name, "lo") != 0) {
            struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
            inet_ntop(AF_INET, &addr->sin_addr, ip, INET_ADDRSTRLEN);
            
            // Предпочитаем не приватные адреса
            if (strncmp(ip, "192.168.", 8) != 0 &&
                strncmp(ip, "10.", 3) != 0 &&
                strncmp(ip, "172.", 4) != 0) {
                break;
            }
        }
    }
    
    freeifaddrs(ifaddr);
    return ip;
}

int start_server(int port) {
    // Создание сокета
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        return -1;
    }
    
    // Настройка сокета
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(server_socket);
        return -1;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    
    // Биндинг
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        return -1;
    }
    
    // Прослушивание
    if (listen(server_socket, MAX_CONNECTIONS) < 0) {
        perror("listen");
        close(server_socket);
        return -1;
    }
    
    // Запуск потока обновления данных
    if (pthread_create(&update_thread, NULL, update_data_thread, NULL) != 0) {
        perror("pthread_create");
        close(server_socket);
        return -1;
    }
    
    printf("\n");
    printf("╔══════════════════════════════════════════╗\n");
    printf("║      System Monitor Server v2.0         ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    printf("✅ Server started successfully!\n");
    printf("🌐 Local:   http://localhost:%d\n", port);
    printf("🌐 Network: http://%s:%d\n", get_local_ip(), port);
    printf("📊 API:     http://localhost:%d/api/system\n", port);
    printf("🏥 Health:  http://localhost:%d/api/health\n", port);
    printf("🛑 Press Ctrl+C to stop\n");
    printf("\n");
    
    // Основной цикл сервера
    while (running) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int client_socket = accept(server_socket, 
                                  (struct sockaddr *)&client_addr, 
                                  &client_len);
        
        if (client_socket < 0) {
            if (running) {
                perror("accept");
            }
            continue;
        }
        
        // Обрабатываем клиента
        handle_client(client_socket);
    }
    
    return 0;
}

void stop_server() {
    running = 0;
    
    if (server_socket != -1) {
        close(server_socket);
        server_socket = -1;
    }
    
    if (update_thread) {
        pthread_join(update_thread, NULL);
    }
}