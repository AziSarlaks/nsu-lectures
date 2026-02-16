class SystemMonitor {
    constructor() {
        console.log('🚀 System Monitor Initializing...');
        this.serverUrl = 'http://localhost:8080';
        this.isOnline = false;
        this.connectionTimeout = 10000; // Увеличили до 10 секунд
        this.historyData = {
            cpu: [],
            memory: [],
            gpu: [],
            gpu_memory: [],
            gpu_temperature: [],
            timestamps: []
        };
        this.historyChart = null;
        this.gpuChart = null;
        this.chartsInitialized = false;
        this.retryDelay = 5000; // Задержка между повторными попытками
        this.maxRetries = 3; // Максимальное количество попыток
        this.currentRetry = 0;
        this.init();
    }

    init() {
        this.setupUI();
        this.setupEventListeners();
        this.tryInitializeCharts();
        this.testConnection();
    }

    setupUI() {
        console.log('Setting up UI...');
        this.updateConnectionStatus('testing', 'Testing connection (timeout: 10s)...');
        this.createLoadingIndicator();
    }

    createLoadingIndicator() {
        // Удаляем старый индикатор если есть
        const oldLoader = document.getElementById('loadingIndicator');
        if (oldLoader) oldLoader.remove();
        
        const loader = document.createElement('div');
        loader.id = 'loadingIndicator';
        loader.className = 'loading-indicator';
        loader.innerHTML = `
            <div class="spinner"></div>
            <span>Connecting to server (timeout: 10s)...</span>
            <div class="progress-bar">
                <div class="progress-fill"></div>
            </div>
        `;
        document.body.appendChild(loader);
    }

    showLoading(show, message = '') {
        const loader = document.getElementById('loadingIndicator');
        if (loader) {
            if (message) {
                const span = loader.querySelector('span');
                if (span) span.textContent = message;
            }
            loader.style.display = show ? 'flex' : 'none';
            
            // Анимация прогресс-бара
            if (show) {
                const progressBar = loader.querySelector('.progress-fill');
                if (progressBar) {
                    progressBar.style.animation = `progress ${this.connectionTimeout}ms linear`;
                }
            }
        }
    }

    async testConnection() {
        console.log(`Testing connection to server (timeout: ${this.connectionTimeout}ms)...`);
        this.showLoading(true, `Connecting to server (${this.currentRetry + 1}/${this.maxRetries})...`);
        
        try {
            const testUrls = [
                'http://localhost:8080/api/system',
                'http://127.0.0.1:8080/api/system',
                'http://localhost:8080/api/health', // Пробуем health endpoint
                'http://127.0.0.1:8080/api/health'
            ];
            
            let connected = false;
            
            for (const url of testUrls) {
                console.log(`Trying URL: ${url}`);
                
                try {
                    const response = await this.fetchWithTimeout(url, this.connectionTimeout);
                    
                    if (response.ok) {
                        console.log(`✅ Successfully connected to: ${url}`);
                        
                        // Определяем основной URL сервера
                        if (url.includes('/api/health')) {
                            this.serverUrl = url.replace('/api/health', '');
                        } else {
                            this.serverUrl = url.replace('/api/system', '');
                        }
                        
                        this.isOnline = true;
                        this.currentRetry = 0;
                        this.updateConnectionStatus('online', 'Online');
                        this.showNotification('Connected to server successfully!', 'success');
                        
                        // Загружаем системные данные
                        await this.loadSystemData();
                        
                        // Загружаем историю
                        await this.loadHistory();
                        
                        // Запускаем периодическое обновление
                        this.startPolling();
                        
                        connected = true;
                        break;
                    }
                } catch (error) {
                    console.log(`Failed to connect to ${url}:`, error.message);
                    continue;
                }
            }
            
            if (!connected) {
                throw new Error(`All ${testUrls.length} connection attempts failed`);
            }
            
        } catch (error) {
            console.error('❌ Connection failed:', error.message);
            
            this.currentRetry++;
            
            if (this.currentRetry < this.maxRetries) {
                // Пробуем снова через delay
                console.log(`Retrying in ${this.retryDelay/1000} seconds... (${this.currentRetry}/${this.maxRetries})`);
                this.updateConnectionStatus('testing', `Retrying... (${this.currentRetry}/${this.maxRetries})`);
                
                // Показываем прогресс перед повторной попыткой
                this.showLoading(true, `Retrying in ${this.retryDelay/1000}s... (${this.currentRetry}/${this.maxRetries})`);
                
                setTimeout(() => {
                    this.testConnection();
                }, this.retryDelay);
                
            } else {
                // Все попытки исчерпаны, переходим в демо-режим
                console.warn(`⚠️ All ${this.maxRetries} retry attempts failed, switching to demo mode`);
                
                this.isOnline = false;
                this.currentRetry = 0;
                this.updateConnectionStatus('offline', 'Offline (Demo Mode)');
                this.showNotification(`Server unavailable after ${this.maxRetries} attempts. Running in demo mode.`, 'warning');
                
                // Запускаем демо-режим
                this.startDemoMode();
            }
            
        } finally {
            this.showLoading(false);
        }
    }

    async fetchWithTimeout(url, timeout) {
        const controller = new AbortController();
        const timeoutId = setTimeout(() => {
            console.log(`Timeout reached for: ${url}`);
            controller.abort();
        }, timeout);
        
        try {
            const response = await fetch(url, {
                signal: controller.signal,
                // Упрощенные заголовки - только Accept
                headers: {
                    'Accept': 'application/json'
                    // Убираем Cache-Control и Pragma - сервер их не разрешает
                },
                mode: 'cors',
                credentials: 'omit'
            });
            
            clearTimeout(timeoutId);
            return response;
        } catch (error) {
            clearTimeout(timeoutId);
            
            if (error.name === 'AbortError') {
                throw new Error(`Request timeout after ${timeout}ms`);
            } else if (error.name === 'TypeError') {
                throw new Error(`Network error: ${error.message}`);
            } else {
                throw error;
            }
        }
    }

    async loadSystemData() {
        if (!this.isOnline) return;
        
        try {
            const response = await this.fetchWithTimeout(`${this.serverUrl}/api/system`, 5000);
            
            if (response.ok) {
                const data = await response.json();
                console.log('📊 System data loaded:', {
                    hasCPU: !!data.cpu,
                    hasMemory: !!data.memory,
                    hasGPU: !!data.gpu,
                    hasProcesses: !!data.processes,
                    processesCount: data.processes?.length || 0
                });
                
                this.updateUI(data);
                this.updateLastUpdate();
            } else {
                console.warn('Failed to load system data:', response.status);
                throw new Error(`HTTP ${response.status}`);
            }
        } catch (error) {
            console.error('Error loading system data:', error);
            throw error;
        }
    }

    async loadHistory() {
        if (!this.isOnline) return;
        
        try {
            const response = await this.fetchWithTimeout(`${this.serverUrl}/api/history`, 5000);
            if (response.ok) {
                const data = await response.json();
                this.historyData = data;
                if (this.chartsInitialized) {
                    this.updateCharts();
                }
            }
        } catch (error) {
            console.error('Failed to load history:', error);
        }
    }

    updateConnectionStatus(status, message = '') {
        const statusEl = document.getElementById('connection-status');
        if (!statusEl) return;
        
        // Убираем все классы статуса
        statusEl.className = 'status-indicator';
        
        switch (status) {
            case 'online':
                statusEl.classList.add('online');
                statusEl.innerHTML = '<i class="fas fa-circle"></i> Online';
                break;
            case 'offline':
                statusEl.classList.add('offline');
                statusEl.innerHTML = '<i class="fas fa-circle"></i> Offline (Demo)';
                break;
            case 'testing':
                statusEl.classList.add('testing');
                statusEl.innerHTML = '<i class="fas fa-sync fa-spin"></i> ' + (message || 'Connecting...');
                break;
            case 'error':
                statusEl.classList.add('error');
                statusEl.innerHTML = '<i class="fas fa-exclamation-circle"></i> Error';
                break;
        }
        
        if (message) {
            statusEl.title = message;
        }
    }

    updateUI(data) {
        console.log('Updating UI with data...');
        
        try {
            // CPU
            if (data.cpu) {
                this.updateCPU(data.cpu);
            }
            
            // Memory
            if (data.memory) {
                this.updateMemory(data.memory);
            }
            
            // GPU
            if (data.gpu) {
                this.updateGPU(data.gpu);
            } else {
                console.warn('No GPU data in response');
                this.updateGPU(this.generateDemoGPU());
            }
            
            // Processes
            if (data.processes) {
                this.updateProcesses(data.processes);
            }
            
        } catch (error) {
            console.error('Error updating UI:', error);
        }
    }

    updateCPU(cpu) {
        const cpuValueEl = document.getElementById('cpuValue');
        if (cpuValueEl && cpu.usage !== undefined) {
            cpuValueEl.textContent = cpu.usage.toFixed(1) + '%';
        }
        
        const cpuCoresEl = document.getElementById('cpuCores');
        if (cpuCoresEl && cpu.cores_count !== undefined) {
            cpuCoresEl.textContent = cpu.cores_count;
        }
        
        this.updateCores(cpu.cores || []);
    }

    updateCores(cores) {
        const container = document.getElementById('coresContainer');
        if (!container) return;
        
        container.innerHTML = '';
        
        const displayCores = cores.slice(0, 24);
        
        displayCores.forEach((core, i) => {
            const usage = core.usage || 0;
            const color = this.getUsageColor(usage);
            
            const coreEl = document.createElement('div');
            coreEl.className = 'core-item';
            coreEl.innerHTML = `
                <div class="core-header">
                    <span class="core-name">C${i.toString().padStart(2, '0')}</span>
                    <span class="core-value">${usage.toFixed(1)}%</span>
                </div>
                <div class="core-bar">
                    <div class="bar-fill" style="width: ${usage}%; background: ${color}"></div>
                </div>
            `;
            container.appendChild(coreEl);
        });
        
        if (displayCores.length === 0) {
            container.innerHTML = '<div class="no-cores">No CPU core data</div>';
        }
    }

    updateMemory(mem) {
        console.log('Updating memory with:', mem);
        
        // Получаем значения в байтах
        const memTotal = mem.total || 0;
        const memUsed = mem.used || 0;
        const memFree = mem.free || 0;
        const memCached = mem.cached || 0;
        const memPercentage = mem.percentage || 0;
        
        console.log('Memory values (bytes):', {
            total: memTotal,
            used: memUsed,
            free: memFree,
            cached: memCached,
            percentage: memPercentage
        });
        
        // Форматируем байты в GB
        const formatGB = (bytes) => {
            if (!bytes || bytes === 0) return '0.0';
            return (bytes / (1024 * 1024 * 1024)).toFixed(1);
        };
        
        const memTotalGB = formatGB(memTotal);
        const memUsedGB = formatGB(memUsed);
        const memFreeGB = formatGB(memFree);
        const memCachedGB = formatGB(memCached);
        
        console.log('Memory values (GB):', {
            total: memTotalGB,
            used: memUsedGB,
            free: memFreeGB,
            cached: memCachedGB,
            percentage: memPercentage.toFixed(1)
        });
        
        // Обновляем значение основного индикатора
        const memValueEl = document.getElementById('memoryValue');
        if (memValueEl) {
            memValueEl.textContent = memPercentage.toFixed(1) + '%';
        }
        
        // Обновляем детали
        const memTotalEl = document.getElementById('memTotal');
        const memUsedEl = document.getElementById('memUsed');
        const memFreeEl = document.getElementById('memFree');
        const memCachedEl = document.getElementById('memCached');
        
        if (memTotalEl) memTotalEl.textContent = memTotalGB + ' GB';
        if (memUsedEl) memUsedEl.textContent = memUsedGB + ' GB';
        if (memFreeEl) memFreeEl.textContent = memFreeGB + ' GB';
        if (memCachedEl) memCachedEl.textContent = memCachedGB + ' GB';
        
        // Обновляем прогресс-бар
        if (memTotal > 0) {
            const usedPercent = (memUsed / memTotal) * 100;
            const cachedPercent = (memCached / memTotal) * 100;
            
            console.log('Progress bar:', {
                usedPercent: usedPercent.toFixed(1),
                cachedPercent: cachedPercent.toFixed(1),
                freePercent: (100 - usedPercent - cachedPercent).toFixed(1)
            });
            
            const usedBar = document.getElementById('memBarUsed');
            const cachedBar = document.getElementById('memBarCached');
            
            if (usedBar) {
                usedBar.style.width = Math.min(100, Math.max(0, usedPercent)) + '%';
                usedBar.style.background = this.getUsageColor(usedPercent);
            }
            
            if (cachedBar) {
                cachedBar.style.width = Math.min(100, Math.max(0, cachedPercent)) + '%';
                cachedBar.style.left = usedPercent + '%';
            }
            
            // Обновляем метки
            const barLabels = document.querySelector('.bar-labels');
            if (barLabels) {
                const freePercent = 100 - usedPercent - cachedPercent;
                barLabels.innerHTML = `
                    <span>Used ${usedPercent.toFixed(1)}%</span>
                    <span>Cached ${cachedPercent.toFixed(1)}%</span>
                    <span>Free ${freePercent.toFixed(1)}%</span>
                `;
            }
        }
        
        // Для демо-режима
        if (!this.isOnline) {
            this.addToLocalHistory('memory', memPercentage);
        }
    }

    updateGPU(gpu) {
        console.log('Updating GPU with:', gpu);
        
        const gpuValueEl = document.getElementById('gpuValue');
        if (gpuValueEl && gpu.usage !== undefined) {
            gpuValueEl.textContent = gpu.usage.toFixed(1) + '%';
        }
        
        // Получаем значения памяти в байтах
        let memTotal = gpu.memory_total || 0;
        let memUsed = gpu.memory_used || 0;
        
        // Проверяем на явно неверные значения (больше 1TB)
        if (memTotal > 1099511627776) { // 1TB в байтах
            console.warn('⚠️ GPU memory_total слишком большой, исправляем:', memTotal);
            memTotal = 8 * 1024 * 1024 * 1024; // 8GB
        }
        
        if (memUsed > memTotal) {
            console.warn('⚠️ GPU memory_used > memory_total, исправляем:', memUsed, '>', memTotal);
            memUsed = memTotal * (gpu.usage / 100);
        }
        
        // Конвертируем байты в GB для отображения
        const formatGB = (bytes) => {
            if (!bytes || bytes === 0) return '0.0';
            const gb = bytes / (1024 * 1024 * 1024);
            return gb.toFixed(1);
        };
        
        const memTotalGB = formatGB(memTotal);
        const memUsedGB = formatGB(memUsed);
        const memPercent = memTotal > 0 ? (memUsed / memTotal) * 100 : 0;
        
        console.log('GPU Memory:', memUsedGB, '/', memTotalGB, 'GB', `(${memPercent.toFixed(1)}%)`);
        
        // Обновляем элементы
        const memUsedEl = document.getElementById('gpuMemUsed');
        const memTotalEl = document.getElementById('gpuMemTotal');
        const memPercentEl = document.getElementById('gpuMemPercent');
        
        if (memUsedEl) memUsedEl.textContent = memUsedGB + ' GB';
        if (memTotalEl) memTotalEl.textContent = memTotalGB + ' GB';
        if (memPercentEl) memPercentEl.textContent = `(${memPercent.toFixed(1)}%)`;
        
        // Температура
        const tempEl = document.getElementById('gpuTemp');
        if (tempEl) {
            tempEl.textContent = gpu.temperature ? 
                `${gpu.temperature.toFixed(1)}°C` : '-- °C';
        }
        
        // Мощность
        const powerEl = document.getElementById('gpuPower');
        if (powerEl) {
            powerEl.textContent = gpu.power ? 
                `${gpu.power.toFixed(1)}W` : '-- W';
        }
        
        // Частота
        const clockEl = document.getElementById('gpuClock');
        if (clockEl) {
            clockEl.textContent = gpu.clock ? 
                `${gpu.clock} MHz` : '-- MHz';
        }
        
        // Имя GPU
        const gpuNameElement = document.querySelector('.gpu-card .card-header h2');
        if (gpuNameElement && gpu.name) {
            gpuNameElement.innerHTML = `<i class="fas fa-gamepad"></i> ${gpu.name}`;
        }
        
        // Прогресс-бар памяти
        const memBar = document.getElementById('gpuMemBar');
        if (memBar && memTotal > 0) {
            memBar.style.width = Math.min(100, Math.max(0, memPercent)) + '%';
            memBar.style.background = this.getUsageColor(memPercent);
        }
        
        // Для демо-режима
        if (!this.isOnline) {
            this.addToLocalHistory('gpu', gpu.usage || 0);
            this.addToLocalHistory('gpu_memory', memPercent);
            this.addToLocalHistory('gpu_temperature', gpu.temperature || 0);
        }
    }

    updateProcesses(processes) {
        const tbody = document.getElementById('processTableBody');
        if (!tbody) return;
        
        const sorted = [...processes].sort((a, b) => (b.cpu || 0) - (a.cpu || 0));
        
        tbody.innerHTML = '';
        
        sorted.slice(0, 15).forEach((proc) => {
            const cpu = proc.cpu || 0;
            const memory = proc.memory || 0;
            const cpuColor = this.getUsageColor(cpu);
            
            const row = document.createElement('tr');
            row.innerHTML = `
                <td class="pid">${proc.pid || '?'}</td>
                <td class="process-name">
                    <span class="process-icon">${(proc.name || '?').charAt(0).toUpperCase()}</span>
                    ${proc.name || 'Unknown'}
                </td>
                <td><span class="status ${this.getProcessStateClass(proc.state)}">${proc.state || '?'}</span></td>
                <td><span class="cpu-value" style="color: ${cpuColor}">${cpu.toFixed(1)}%</span></td>
                <td>${this.formatBytes(memory)}</td>
                <td class="command" title="${proc.command || ''}">
                    ${this.truncateText(proc.command || '', 40)}
                </td>
            `;
            
            tbody.appendChild(row);
        });
        
        document.getElementById('processCount').textContent = `${processes.length} processes`;
    }

    updateLastUpdate() {
        const now = new Date();
        const timeStr = now.toLocaleTimeString([], { 
            hour: '2-digit', 
            minute: '2-digit', 
            second: '2-digit' 
        });
        
        const updateEl = document.getElementById('last-update');
        if (updateEl) {
            updateEl.innerHTML = `<i class="far fa-clock"></i> Last update: ${timeStr}`;
        }
    }

    startPolling() {
        console.log('Starting polling every 2 seconds...');
        
        if (this.pollInterval) {
            clearInterval(this.pollInterval);
        }
        
        this.pollInterval = setInterval(() => {
            if (this.isOnline) {
                this.loadSystemData();
                this.loadHistory();
            }
        }, 2000);
    }

    startDemoMode() {
        console.log('Starting demo mode...');
        
        if (this.demoInterval) {
            clearInterval(this.demoInterval);
        }
        
        // Инициализируем демо-историю
        this.initializeDemoHistory();
        
        // Генерируем демо-данные
        this.generateDemoData();
        
        // Обновляем каждые 2 секунды
        this.demoInterval = setInterval(() => {
            this.generateDemoData();
        }, 2000);
        
        // Показываем уведомление
        this.showDemoNotice();
    }

    initializeDemoHistory() {
        for (let i = 0; i < 30; i++) {
            const timeOffset = (29 - i) * 2;
            
            this.historyData.timestamps.unshift(Math.floor((Date.now() - timeOffset * 1000) / 1000));
            this.historyData.cpu.unshift(20 + Math.random() * 40);
            this.historyData.memory.unshift(30 + Math.random() * 40);
            this.historyData.gpu.unshift(15 + Math.random() * 50);
            this.historyData.gpu_memory.unshift(20 + Math.random() * 60);
            this.historyData.gpu_temperature.unshift(40 + Math.random() * 30);
        }
        
        this.historyData.count = 30;
        
        if (this.chartsInitialized) {
            this.updateCharts();
        }
    }

    generateDemoData() {
        const demoData = {
            cpu: {
                usage: 20 + Math.random() * 60,
                cores_count: 8,
                cores: Array.from({length: 8}, (_, i) => ({
                    core: i,
                    usage: 10 + Math.random() * 70
                }))
            },
            memory: {
                total: 16 * 1024 * 1024 * 1024,
                used: (16 * 1024 * 1024 * 1024) * (0.3 + Math.random() * 0.5),
                free: (16 * 1024 * 1024 * 1024) * (0.2 + Math.random() * 0.3),
                cached: (16 * 1024 * 1024 * 1024) * (0.05 + Math.random() * 0.1),
                percentage: 30 + Math.random() * 50
            },
            gpu: this.generateDemoGPU(),
            processes: this.generateDemoProcesses()
        };
        
        this.updateUI(demoData);
        this.updateLastUpdate();
    }

    generateDemoGPU() {
        const usage = 15 + Math.random() * 70;
        const memoryTotal = 8 * 1024 * 1024 * 1024;
        
        return {
            usage: usage,
            memory: {
                total: memoryTotal,
                used: memoryTotal * (usage / 100)
            },
            temperature: 45 + usage * 0.3,
            power: 60 + usage * 0.7,
            clock: 1500 + Math.random() * 600,
            name: 'NVIDIA GeForce RTX 3060 (Demo)'
        };
    }

    generateDemoProcesses() {
        const processList = [
            { name: 'systemd', cpu: 0.5, memory: 1024000 },
            { name: 'bash', cpu: 0.3, memory: 2048000 },
            { name: 'chrome', cpu: 8 + Math.random() * 20, memory: 200000000 },
            { name: 'code', cpu: 3 + Math.random() * 8, memory: 300000000 },
            { name: 'node', cpu: 1 + Math.random() * 5, memory: 100000000 }
        ];
        
        return processList.map((proc, i) => ({
            pid: 1000 + i,
            name: proc.name,
            state: ['R', 'S', 'D'][Math.floor(Math.random() * 3)],
            memory: proc.memory,
            cpu: proc.cpu,
            command: `/usr/bin/${proc.name} --demo-mode`
        })).sort((a, b) => b.cpu - a.cpu);
    }

    showDemoNotice() {
        const oldNotice = document.querySelector('.demo-notice');
        if (oldNotice) oldNotice.remove();
        
        const notice = document.createElement('div');
        notice.className = 'demo-notice';
        notice.innerHTML = `
            <div class="demo-content">
                <i class="fas fa-info-circle"></i>
                <span>Running in demo mode. Server unavailable.</span>
                <div class="demo-actions">
                    <button id="retryConnection" class="btn-retry">
                        <i class="fas fa-redo"></i> Retry Connection
                    </button>
                    <button id="openServerConfig" class="btn-config">
                        <i class="fas fa-server"></i> Server Info
                    </button>
                </div>
            </div>
        `;
        
        document.body.appendChild(notice);
        
        document.getElementById('retryConnection').addEventListener('click', () => {
            this.retryConnection();
        });
        
        document.getElementById('openServerConfig').addEventListener('click', () => {
            this.showServerInfo();
        });
    }

    async retryConnection() {
        console.log('Retrying connection...');
        
        const notice = document.querySelector('.demo-notice');
        if (notice) notice.remove();
        
        if (this.demoInterval) {
            clearInterval(this.demoInterval);
            this.demoInterval = null;
        }
        
        this.updateConnectionStatus('testing', 'Retrying connection...');
        await this.testConnection();
    }

    showServerInfo() {
        const info = `
            <div class="server-info-modal">
                <h3>Server Connection Info</h3>
                <p><strong>Expected URL:</strong> http://localhost:8080</p>
                <p><strong>API Endpoints:</strong></p>
                <ul>
                    <li>GET /api/system - System data</li>
                    <li>GET /api/history - History data</li>
                    <li>GET /api/health - Health check</li>
                </ul>
                <p><strong>To start the server:</strong></p>
                <pre>./monitor_server</pre>
                <p><strong>Check if server is running:</strong></p>
                <pre>curl http://localhost:8080/api/health</pre>
            </div>
        `;
        
        this.showNotification('Check browser console for server info', 'info');
        console.info('Server Connection Info:', {
            expectedUrl: 'http://localhost:8080',
            endpoints: [
                'GET /api/system',
                'GET /api/history', 
                'GET /api/health'
            ],
            startCommand: './monitor_server',
            testCommand: 'curl http://localhost:8080/api/health'
        });
    }

    getUsageColor(value) {
        if (value >= 90) return '#e74c3c';
        if (value >= 70) return '#e67e22';
        if (value >= 50) return '#f1c40f';
        if (value >= 30) return '#3498db';
        return '#2ecc71';
    }

    getProcessStateClass(state) {
        const map = {
            'R': 'running',
            'S': 'sleeping',
            'D': 'disk',
            'Z': 'zombie',
            'T': 'stopped'
        };
        return map[state] || 'unknown';
    }

    formatBytes(bytes) {
        if (!bytes) return '0 B';
        
        const units = ['B', 'KB', 'MB', 'GB', 'TB'];
        const i = Math.floor(Math.log(bytes) / Math.log(1024));
        
        return `${(bytes / Math.pow(1024, i)).toFixed(i > 0 ? 1 : 0)} ${units[i]}`;
    }

    truncateText(text, maxLength) {
        if (!text) return '';
        if (text.length <= maxLength) return text;
        return text.substring(0, maxLength - 3) + '...';
    }

    showNotification(message, type = 'info') {
        const toast = document.createElement('div');
        toast.className = `toast toast-${type}`;
        toast.innerHTML = `
            <i class="fas fa-${type === 'success' ? 'check-circle' : 'info-circle'}"></i>
            <span>${message}</span>
        `;
        
        document.body.appendChild(toast);
        
        setTimeout(() => toast.classList.add('show'), 10);
        
        setTimeout(() => {
            toast.classList.remove('show');
            setTimeout(() => toast.remove(), 300);
        }, 3000);
    }

    setupEventListeners() {
        document.getElementById('refreshBtn')?.addEventListener('click', () => {
            if (this.isOnline) {
                this.loadSystemData();
                this.loadHistory();
            } else {
                this.generateDemoData();
            }
            
            const btn = document.getElementById('refreshBtn');
            btn.classList.add('spin');
            setTimeout(() => btn.classList.remove('spin'), 1000);
        });
        
        document.getElementById('themeToggle')?.addEventListener('click', () => {
            this.toggleTheme();
        });
        
        document.getElementById('searchProcess')?.addEventListener('input', (e) => {
            this.filterProcesses(e.target.value);
        });
        
        document.getElementById('sortBy')?.addEventListener('change', () => {
            if (this.isOnline) {
                this.loadSystemData();
            }
        });
        
        document.getElementById('updateInterval')?.addEventListener('change', (e) => {
            this.updatePollingInterval(parseInt(e.target.value));
        });
        
        document.getElementById('historyRange')?.addEventListener('change', (e) => {
            this.updateHistoryRange(parseInt(e.target.value));
        });
    }

    filterProcesses(searchTerm) {
        const rows = document.querySelectorAll('#processTableBody tr');
        const term = searchTerm.toLowerCase();
        
        rows.forEach(row => {
            const name = row.querySelector('.process-name').textContent.toLowerCase();
            const command = row.querySelector('.command').textContent.toLowerCase();
            const pid = row.querySelector('.pid').textContent;
            
            const matches = name.includes(term) || 
                          command.includes(term) || 
                          pid.includes(term);
            
            row.style.display = matches ? '' : 'none';
        });
    }

    toggleTheme() {
        const isDark = document.documentElement.getAttribute('data-theme') === 'dark';
        const newTheme = isDark ? 'light' : 'dark';
        
        document.documentElement.setAttribute('data-theme', newTheme);
        localStorage.setItem('sysmon-theme', newTheme);
        
        this.showNotification(`${newTheme} theme enabled`);
    }

    updatePollingInterval(interval) {
        if (this.pollInterval) {
            clearInterval(this.pollInterval);
        }
        
        if (this.isOnline) {
            this.pollInterval = setInterval(() => {
                this.loadSystemData();
                this.loadHistory();
            }, interval);
        }
        
        this.showNotification(`Update interval: ${interval/1000}s`);
    }

    updateHistoryRange(minutes) {
        this.showNotification(`Showing last ${minutes} minutes of history`);
    }

    tryInitializeCharts() {
        if (typeof Chart !== 'undefined') {
            this.initializeCharts();
            this.chartsInitialized = true;
            console.log('✅ Charts initialized successfully');
        } else {
            console.warn('⚠️ Chart.js not loaded yet, will try again in 1 second');
            setTimeout(() => this.tryInitializeCharts(), 1000);
        }
    }

    initializeCharts() {
        console.log('📊 Initializing charts...');
        
        // Инициализация основного графика истории
        const historyCtx = document.getElementById('historyChart')?.getContext('2d');
        if (historyCtx) {
            this.historyChart = new Chart(historyCtx, {
                type: 'line',
                data: {
                    labels: [],
                    datasets: [
                        {
                            label: 'CPU Usage %',
                            data: [],
                            borderColor: '#3498db',
                            backgroundColor: 'rgba(52, 152, 219, 0.1)',
                            borderWidth: 2,
                            fill: true,
                            tension: 0.4,
                            pointRadius: 0
                        },
                        {
                            label: 'Memory Usage %',
                            data: [],
                            borderColor: '#2ecc71',
                            backgroundColor: 'rgba(46, 204, 113, 0.1)',
                            borderWidth: 2,
                            fill: true,
                            tension: 0.4,
                            pointRadius: 0
                        }
                    ]
                },
                options: {
                    responsive: true,
                    maintainAspectRatio: false,
                    plugins: {
                        legend: {
                            position: 'top',
                            labels: {
                                usePointStyle: true,
                                padding: 20
                            }
                        },
                        tooltip: {
                            mode: 'index',
                            intersect: false,
                            callbacks: {
                                label: function(context) {
                                    return `${context.dataset.label}: ${context.parsed.y.toFixed(1)}%`;
                                }
                            }
                        }
                    },
                    scales: {
                        y: {
                            beginAtZero: true,
                            max: 100,
                            grid: {
                                color: 'rgba(0, 0, 0, 0.05)'
                            },
                            title: {
                                display: true,
                                text: 'Percentage (%)',
                                color: '#666'
                            },
                            ticks: {
                                color: '#666'
                            }
                        },
                        x: {
                            grid: {
                                color: 'rgba(0, 0, 0, 0.05)'
                            },
                            ticks: {
                                color: '#666',
                                maxRotation: 0
                            }
                        }
                    },
                    animation: {
                        duration: 0
                    }
                }
            });
            console.log('✅ History chart initialized');
        } else {
            console.warn('⚠️ History chart canvas not found');
        }

        // Инициализация графика GPU истории
        const gpuCtx = document.getElementById('gpuChart')?.getContext('2d');
        if (gpuCtx) {
            this.gpuChart = new Chart(gpuCtx, {
                type: 'line',
                data: {
                    labels: [],
                    datasets: [
                        {
                            label: 'GPU Usage %',
                            data: [],
                            borderColor: '#9b59b6',
                            backgroundColor: 'rgba(155, 89, 182, 0.1)',
                            borderWidth: 2,
                            fill: true,
                            tension: 0.4,
                            pointRadius: 0
                        },
                        {
                            label: 'GPU Memory %',
                            data: [],
                            borderColor: '#e74c3c',
                            backgroundColor: 'rgba(231, 76, 60, 0.1)',
                            borderWidth: 2,
                            fill: true,
                            tension: 0.4,
                            pointRadius: 0
                        },
                        {
                            label: 'GPU Temperature °C',
                            data: [],
                            borderColor: '#f39c12',
                            backgroundColor: 'rgba(243, 156, 18, 0.1)',
                            borderWidth: 2,
                            fill: false,
                            tension: 0.4,
                            pointRadius: 0,
                            yAxisID: 'y2'
                        }
                    ]
                },
                options: {
                    responsive: true,
                    maintainAspectRatio: false,
                    plugins: {
                        legend: {
                            position: 'top',
                            labels: {
                                usePointStyle: true,
                                padding: 20
                            }
                        },
                        tooltip: {
                            mode: 'index',
                            intersect: false,
                            callbacks: {
                                label: function(context) {
                                    if (context.datasetIndex === 2) {
                                        return `${context.dataset.label}: ${context.parsed.y.toFixed(1)}°C`;
                                    }
                                    return `${context.dataset.label}: ${context.parsed.y.toFixed(1)}%`;
                                }
                            }
                        }
                    },
                    scales: {
                        y: {
                            beginAtZero: true,
                            max: 100,
                            grid: {
                                color: 'rgba(0, 0, 0, 0.05)'
                            },
                            title: {
                                display: true,
                                text: 'Percentage (%)',
                                color: '#666'
                            },
                            ticks: {
                                color: '#666'
                            }
                        },
                        y2: {
                            position: 'right',
                            beginAtZero: true,
                            max: 100,
                            grid: {
                                drawOnChartArea: false
                            },
                            title: {
                                display: true,
                                text: 'Temperature (°C)',
                                color: '#666'
                            },
                            ticks: {
                                color: '#666'
                            }
                        },
                        x: {
                            grid: {
                                color: 'rgba(0, 0, 0, 0.05)'
                            },
                            ticks: {
                                color: '#666',
                                maxRotation: 0
                            }
                        }
                    },
                    animation: {
                        duration: 0
                    }
                }
            });
            console.log('✅ GPU history chart initialized');
        } else {
            console.warn('⚠️ GPU history chart canvas not found');
        }
    }

    updateCharts() {
        if (!this.historyChart || !this.gpuChart) return;
        
        // Обновляем основной график истории
        if (this.historyChart && this.historyData.timestamps.length > 0) {
            const timestamps = this.historyData.timestamps.map(ts => {
                const date = new Date(ts * 1000);
                return date.toLocaleTimeString([], { 
                    hour: '2-digit', 
                    minute: '2-digit' 
                });
            });
            
            this.historyChart.data.labels = timestamps;
            this.historyChart.data.datasets[0].data = this.historyData.cpu;
            this.historyChart.data.datasets[1].data = this.historyData.memory;
            this.historyChart.update();
            
            console.log(`📈 Updated history chart with ${this.historyData.timestamps.length} points`);
        }
        
        // Обновляем график GPU истории
        if (this.gpuChart && this.historyData.timestamps.length > 0) {
            const timestamps = this.historyData.timestamps.map(ts => {
                const date = new Date(ts * 1000);
                return date.toLocaleTimeString([], { 
                    hour: '2-digit', 
                    minute: '2-digit' 
                });
            });
            
            this.gpuChart.data.labels = timestamps;
            this.gpuChart.data.datasets[0].data = this.historyData.gpu;
            this.gpuChart.data.datasets[1].data = this.historyData.gpu_memory;
            this.gpuChart.data.datasets[2].data = this.historyData.gpu_temperature;
            this.gpuChart.update();
            
            console.log(`🎮 Updated GPU chart with ${this.historyData.timestamps.length} points`);
        }
    }
}

// Запускаем при загрузке DOM
document.addEventListener('DOMContentLoaded', () => {
    console.log('📄 DOM loaded, starting SystemMonitor...');
    
    if (typeof Chart === 'undefined') {
        console.warn('⚠️ Chart.js not loaded, loading it now...');
        
        const script = document.createElement('script');
        script.src = 'https://cdn.jsdelivr.net/npm/chart.js';
        script.onload = () => {
            console.log('✅ Chart.js loaded successfully');
            window.sysmon = new SystemMonitor();
        };
        script.onerror = () => {
            console.error('❌ Failed to load Chart.js, charts will not work');
            window.sysmon = new SystemMonitor();
        };
        document.head.appendChild(script);
    } else {
        window.sysmon = new SystemMonitor();
    }
});