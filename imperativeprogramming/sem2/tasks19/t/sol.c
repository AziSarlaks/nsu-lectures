#include "sol.h"
#include <stdlib.h>

#define MAX_N 300005
#define INIT_CAPACITY 10

typedef struct {
    int *to;
    int *weight;
    int size;
    int capacity;
} EdgeList;

EdgeList *incident;
int N;

void init() {
    N = getVerticesCount();
    
    incident = (EdgeList*)malloc(N * sizeof(EdgeList));
    for (int i = 0; i < N; i++) {
        incident[i].size = 0;
        incident[i].capacity = INIT_CAPACITY;
        incident[i].to = (int*)malloc(INIT_CAPACITY * sizeof(int));
        incident[i].weight = (int*)malloc(INIT_CAPACITY * sizeof(int));
    }
    
    Edge e;
    while (readEdge(&e)) {
        if (incident[e.from].size >= incident[e.from].capacity) {
            incident[e.from].capacity *= 2;
            incident[e.from].to = (int*)realloc(incident[e.from].to, incident[e.from].capacity * sizeof(int));
            incident[e.from].weight = (int*)realloc(incident[e.from].weight, incident[e.from].capacity * sizeof(int));
        }
        incident[e.from].to[incident[e.from].size] = e.to;
        incident[e.from].weight[incident[e.from].size] = e.weight;
        incident[e.from].size++;
        
        if (incident[e.to].size >= incident[e.to].capacity) {
            incident[e.to].capacity *= 2;
            incident[e.to].to = (int*)realloc(incident[e.to].to, incident[e.to].capacity * sizeof(int));
            incident[e.to].weight = (int*)realloc(incident[e.to].weight, incident[e.to].capacity * sizeof(int));
        }
        incident[e.to].to[incident[e.to].size] = e.from;
        incident[e.to].weight[incident[e.to].size] = e.weight;
        incident[e.to].size++;
    }
}

int getEdgesCount(int iVertex) {
    return incident[iVertex].size;
}

Edge getIncidentEdge(int iVertex, int iIndex) {
    Edge result;
    result.from = iVertex;
    result.to = incident[iVertex].to[iIndex];
    result.weight = incident[iVertex].weight[iIndex];
    return result;
}