#include <stdio.h>
#define V 4  // Number of vertices

int isSafe(int v, int graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c)
            return 0;
    return 1;
}

int graphColoringUtil(int graph[V][V], int m, int color[], int v) {
    if (v == V)
        return 1;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;
            if (graphColoringUtil(graph, m, color, v + 1))
                return 1;
            color[v] = 0; // backtrack
        }
    }
    return 0;
}

void graphColoring(int graph[V][V], int m) {
    int color[V] = {0};
    if (!graphColoringUtil(graph, m, color, 0)) {
        printf("Solution does not exist");
        return;
    }

    printf("Assigned colors: ");
    for (int i = 0; i < V; i++)
        printf("%d ", color[i]);
}

int main() {
    int graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };
    int m = 3; // Number of colors
    graphColoring(graph, m);
    return 0;
}
