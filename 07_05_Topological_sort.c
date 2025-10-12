#include <stdio.h>
#define MAX 100

int visited[MAX];
int stack[MAX], top = -1;

void topoUtil(int v, int graph[MAX][MAX], int V) {
    visited[v] = 1;
    for (int i = 0; i < V; i++)
        if (graph[v][i] && !visited[i])
            topoUtil(i, graph, V);
    stack[++top] = v;  // push after visiting all neighbors
}

void topologicalSort(int graph[MAX][MAX], int V) {
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    for (int i = 0; i < V; i++)
        if (!visited[i])
            topoUtil(i, graph, V);

    printf("Topological order: ");
    while (top >= 0)
        printf("%d ", stack[top--]);
}

int main() {
    int V = 6;
    int graph[MAX][MAX] = {
        {0,1,1,0,0,0},
        {0,0,0,1,1,0},
        {0,0,0,1,0,0},
        {0,0,0,0,0,1},
        {0,0,0,0,0,1},
        {0,0,0,0,0,0}
    };
    topologicalSort(graph, V);
    return 0;
}
