#ifndef CONFIG_H
#define CONFIG_H

#define PORT 8080
#define BUFFER_SIZE 4096
#define MAX_PROCESSES 512
#define UPDATE_INTERVAL_MS 2000
#define MAX_CONNECTIONS 10
#define MAX_CORES 32

typedef struct {
    unsigned long long total;
    unsigned long long used;
    unsigned long long free;
    unsigned long long cached;
    double percentage;
} MemoryInfo;

typedef struct {
    double user;
    double nice;
    double system;
    double idle;
    double iowait;
    double irq;
    double softirq;
    double steal;
    double guest;
    double guest_nice;
    double total;
    double usage_percent;
} CPUStats;

typedef struct {
    int pid;
    char name[256];
    char state;
    unsigned long utime;
    unsigned long stime;
    long rss;
    double cpu_usage;
    double mem_usage;
    char command_line[512];
} ProcessInfo;

#endif