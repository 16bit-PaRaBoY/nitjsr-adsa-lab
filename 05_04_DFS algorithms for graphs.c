#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int timeCounter;        // Global timer
int discovery[MAX];     // Discovery time
int finish[MAX];        // Finish time
int visited[MAX];       // 0 = not visited, 1 = visiting, 2 = finished

// DFS function
void DFS(int u, int graph[MAX][MAX], int V) {
    visited[u] = 1;
    discovery[u] = ++timeCounter;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) { // Edge u -> v exists
            if (visited[v] == 0) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFS(v, graph, V);
            }
            else if (visited[v] == 1) {
                printf("Back Edge: %d -> %d\n", u, v);
            }
            else if (visited[v] == 2) {
                if (discovery[u] < discovery[v])
                    printf("Forward Edge: %d -> %d\n", u, v);
                else
                    printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }

    visited[u] = 2;
    finish[u] = ++timeCounter;
}

// Run DFS on all vertices
void runDFS(int graph[MAX][MAX], int V) {
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        discovery[i] = finish[i] = -1;
    }
    timeCounter = 0;

    for (int i = 0; i < V; i++) {
        if (visited[i] == 0)
            DFS(i, graph, V);
    }
}

int main() {
    int V = 6; // number of vertices
    int graph[MAX][MAX] = {0};

    // Example directed graph
    graph[0][1] = 1;
    graph[0][2] = 1;
    graph[1][3] = 1;
    graph[2][3] = 1;
    graph[3][4] = 1;
    graph[4][1] = 1; // back edge
    graph[4][5] = 1;

    runDFS(graph, V);

    return 0;
}
