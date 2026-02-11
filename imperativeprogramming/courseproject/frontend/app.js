class SystemMonitor {
    constructor() {
        console.log('🚀 System Monitor Initializing...');
        this.serverUrl = 'http://localhost:8080';
        this.isOnline = false;
        this.init();
    }

    init() {
        this.setupUI();
        this.setupEventListeners();
        this.testConnection();
    }

    setupUI() {
        console.log('Setting up UI...');
        this.updateConnectionStatus('testing', 'Connecting...');
        
        // Скрываем GPU карточки (сервер не предоставляет GPU данные)
        this.hideGPUCard();
    }

    async testConnection() {
        console.log('Testing connection to server...');
        
        try {
            const response = await fetch(`${this.serverUrl}/api/system`, {
                headers: { 'Accept': 'application/json' }
            });
            
            console.log('Response status:', response.status);
            
            if (response.ok) {
                const data = await response.json();
                console.log('✅ Connected successfully!', data);
                
                this.isOnline = true;
                this.updateConnectionStatus('online', 'Online');
                this.showNotification('Connected to server!', 'success');
                
                // Обновляем UI с реальными данными
                this.updateUI(data);
                
                // Запускаем периодическое обновление
                this.startPolling();
                
                return true;
            } else {
                throw new Error(`HTTP ${response.status}`);
            }
        } catch (error) {
            console.error('❌ Connection failed:', error);
            
            this.isOnline = false;
            this.updateConnectionStatus('offline', 'Offline (Demo)');
            this.showNotification('Server unavailable. Demo mode.', 'warning');
            
            // Запускаем демо-режим
            this.startDemoMode();
            
            return false;
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
                statusEl.innerHTML = '<i class="fas fa-sync fa-spin"></i> Connecting...';
                break;
        }
        
        if (message) {
            statusEl.title = message;
        }
    }

    updateUI(data) {
        console.log('Updating UI with data:', data);
        
        try {
            // CPU
            if (data.cpu) {
                this.updateCPU(data.cpu);
            }
            
            // Memory
            if (data.memory) {
                this.updateMemory(data.memory);
            }
            
            // Processes
            if (data.processes) {
                this.updateProcesses(data.processes);
            }
            
            // Обновляем время последнего обновления
            this.updateLastUpdate();
            
        } catch (error) {
            console.error('Error updating UI:', error);
        }
    }

    updateCPU(cpu) {
        // Обновляем общее использование CPU
        const cpuValueEl = document.getElementById('cpuValue');
        if (cpuValueEl && cpu.usage !== undefined) {
            cpuValueEl.textContent = cpu.usage.toFixed(1) + '%';
        }
        
        // Обновляем количество ядер
        const cpuCoresEl = document.getElementById('cpuCores');
        if (cpuCoresEl && cpu.cores_count !== undefined) {
            cpuCoresEl.textContent = cpu.cores_count;
        }
        
        // Обновляем ядра
        this.updateCores(cpu.cores || []);
    }

    updateCores(cores) {
        const container = document.getElementById('coresContainer');
        if (!container) return;
        
        // Очищаем контейнер
        container.innerHTML = '';
        
        // Добавляем ядра (максимум 24 для отображения)
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
        
        // Если нет ядер, показываем сообщение
        if (displayCores.length === 0) {
            container.innerHTML = '<div class="no-cores">No CPU core data</div>';
        }
    }

    updateMemory(mem) {
        // Обновляем общее использование памяти
        const memValueEl = document.getElementById('memoryValue');
        if (memValueEl && mem.percentage !== undefined) {
            memValueEl.textContent = mem.percentage.toFixed(1) + '%';
        }
        
        // Форматируем байты в GB
        const formatGB = (bytes) => {
            return (bytes / (1024 * 1024 * 1024)).toFixed(1);
        };
        
        // Обновляем детали памяти
        if (mem.total !== undefined) {
            document.getElementById('memTotal').textContent = formatGB(mem.total) + ' GB';
        }
        if (mem.used !== undefined) {
            document.getElementById('memUsed').textContent = formatGB(mem.used) + ' GB';
        }
        if (mem.free !== undefined) {
            document.getElementById('memFree').textContent = formatGB(mem.free) + ' GB';
        }
        if (mem.cached !== undefined) {
            document.getElementById('memCached').textContent = formatGB(mem.cached) + ' GB';
        }
        
        // Обновляем прогресс-бар
        if (mem.total > 0) {
            const usedPercent = (mem.used / mem.total) * 100;
            const cachedPercent = (mem.cached / mem.total) * 100;
            
            const usedBar = document.getElementById('memBarUsed');
            const cachedBar = document.getElementById('memBarCached');
            
            if (usedBar) {
                usedBar.style.width = usedPercent + '%';
                usedBar.style.background = this.getUsageColor(usedPercent);
            }
            
            if (cachedBar) {
                cachedBar.style.width = cachedPercent + '%';
                cachedBar.style.left = usedPercent + '%';
            }
        }
    }

    updateProcesses(processes) {
        const tbody = document.getElementById('processTableBody');
        if (!tbody) return;
        
        // Сортируем по использованию CPU
        const sorted = [...processes].sort((a, b) => (b.cpu || 0) - (a.cpu || 0));
        
        // Очищаем таблицу
        tbody.innerHTML = '';
        
        // Добавляем процессы (максимум 15)
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
        
        // Обновляем счетчик процессов
        document.getElementById('processCount').textContent = `${processes.length} processes`;
    }

    hideGPUCard() {
        const gpuCard = document.querySelector('.gpu-card');
        const gpuHistoryCard = document.querySelector('.gpu-history-card');
        
        if (gpuCard) gpuCard.style.display = 'none';
        if (gpuHistoryCard) gpuHistoryCard.style.display = 'none';
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
        
        // Обновляем каждые 2 секунды
        setInterval(() => {
            if (this.isOnline) {
                this.fetchData();
            }
        }, 2000);
    }

    async fetchData() {
        try {
            const response = await fetch(`${this.serverUrl}/api/system`);
            
            if (response.ok) {
                const data = await response.json();
                this.updateUI(data);
            } else {
                console.warn('Fetch failed:', response.status);
            }
        } catch (error) {
            console.error('Fetch error:', error);
        }
    }

    startDemoMode() {
        console.log('Starting demo mode...');
        
        // Показываем GPU в демо-режиме
        const gpuCard = document.querySelector('.gpu-card');
        const gpuHistoryCard = document.querySelector('.gpu-history-card');
        if (gpuCard) gpuCard.style.display = 'block';
        if (gpuHistoryCard) gpuHistoryCard.style.display = 'block';
        
        // Генерируем демо-данные
        this.generateDemoData();
        
        // Обновляем каждые 2 секунды
        setInterval(() => {
            this.generateDemoData();
        }, 2000);
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
            processes: this.generateDemoProcesses()
        };
        
        this.updateUI(demoData);
        this.updateLastUpdate();
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
            command: `/usr/bin/${proc.name}`
        })).sort((a, b) => b.cpu - a.cpu);
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
        // Кнопка обновления
        document.getElementById('refreshBtn')?.addEventListener('click', () => {
            if (this.isOnline) {
                this.fetchData();
            } else {
                this.generateDemoData();
            }
        });
        
        // Переключение темы
        document.getElementById('themeToggle')?.addEventListener('click', () => {
            this.toggleTheme();
        });
    }

    toggleTheme() {
        const isDark = document.documentElement.getAttribute('data-theme') === 'dark';
        const newTheme = isDark ? 'light' : 'dark';
        
        document.documentElement.setAttribute('data-theme', newTheme);
        localStorage.setItem('sysmon-theme', newTheme);
        
        this.showNotification(`${newTheme} theme enabled`);
    }
}

// Запускаем при загрузке DOM
document.addEventListener('DOMContentLoaded', () => {
    console.log('📄 DOM loaded, starting SystemMonitor...');
    window.sysmon = new SystemMonitor();
});