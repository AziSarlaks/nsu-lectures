# server.h
cat > backend/src/server.h << 'EOF'
#ifndef SERVER_H
#define SERVER_H

int start_server(int port);
void stop_server();

#endif
EOF

# system_info.h
cat > backend/src/system_info.h << 'EOF'
#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include "config.h"

void collect_system_info(CPUStats *cpu, MemoryInfo *mem);

#endif
EOF

# proc_parser.h
cat > backend/src/proc_parser.h << 'EOF'
#ifndef PROC_PARSER_H
#define PROC_PARSER_H

#include "config.h"

int read_cpu_stats(CPUStats *cpu);
int read_memory_info(MemoryInfo *mem);
int get_processes(ProcessInfo *processes, int *count);

#endif
EOF

# json_formatter.h
cat > backend/src/json_formatter.h << 'EOF'
#ifndef JSON_FORMATTER_H
#define JSON_FORMATTER_H

#include "config.h"

void format_system_info_json(char *buffer, int buffer_size, 
                            CPUStats *cpu, MemoryInfo *mem,
                            ProcessInfo *processes, int process_count);

#endif
EOF