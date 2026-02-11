class SystemMonitor {
    constructor() {
        console.log('SystemMonitor initialized');
        this.init();
    }

    init() {
        console.log('Testing connection...');
        this.testConnection();
    }

    async testConnection() {
        try {
            console.log('Fetching from: http://localhost:8080/api/system');
            
            const response = await fetch('http://localhost:8080/api/system', {
                headers: { 'Accept': 'application/json' }
            });
            
            console.log('Response:', response.status, response.statusText);
            
            if (response.ok) {
                const data = await response.json();
                console.log('✅ Connected! Data:', data);
                this.updateUI(data);
                this.startPolling();
            } else {
                throw new Error(`HTTP ${response.status}`);
            }
        } catch (error) {
            console.error('❌ Connection failed:', error);
            this.startDemoMode();
        }
    }

    updateUI(data) {
        console.log('Updating UI with:', data);
        
        // Обновляем CPU
        if (data.cpu && data.cpu.usage) {
            const cpuEl = document.getElementById('cpuValue');
            if (cpuEl) cpuEl.textContent = data.cpu.usage.toFixed(1) + '%';
        }
        
        // Обновляем Memory
        if (data.memory && data.memory.percentage) {
            const memEl = document.getElementById('memoryValue');
            if (memEl) memEl.textContent = data.memory.percentage.toFixed(1) + '%';
        }
        
        // Обновляем статус
        const statusEl = document.getElementById('connection-status');
        if (statusEl) {
            statusEl.innerHTML = '<i class="fas fa-circle"></i> Online';
            statusEl.className = 'status-indicator online';
        }
        
        // Обновляем время
        this.updateLastUpdate();
    }

    updateLastUpdate() {
        const now = new Date();
        const timeStr = now.toLocaleTimeString();
        const updateEl = document.getElementById('last-update');
        if (updateEl) {
            updateEl.innerHTML = `<i class="far fa-clock"></i> Last update: ${timeStr}`;
        }
    }

    startPolling() {
        console.log('Starting polling...');
        setInterval(() => {
            this.testConnection();
        }, 2000);
    }

    startDemoMode() {
        console.log('Starting demo mode...');
        
        // Обновляем статус
        const statusEl = document.getElementById('connection-status');
        if (statusEl) {
            statusEl.innerHTML = '<i class="fas fa-circle"></i> Offline (Demo)';
            statusEl.className = 'status-indicator offline';
        }
        
        // Генерируем демо-данные
        setInterval(() => {
            const demoData = {
                cpu: { usage: 20 + Math.random() * 60 },
                memory: { percentage: 30 + Math.random() * 50 },
                processes: []
            };
            this.updateUI(demoData);
        }, 2000);
    }
}

// Запускаем при загрузке страницы
document.addEventListener('DOMContentLoaded', () => {
    console.log('DOM loaded, starting SystemMonitor...');
    window.monitor = new SystemMonitor();
});