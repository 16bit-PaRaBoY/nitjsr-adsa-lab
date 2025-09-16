#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5   // Number of vertices in the graph

// Find the vertex with the minimum key value
int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print the constructed MST
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
}

// Prim’s algorithm to construct MST
void primMST(int graph[V][V]) {
    int parent[V];   // Stores MST structure
    int key[V];      // Key values to pick minimum edge
    bool mstSet[V];  // To represent vertices included in MST

    // Initialize all keys as infinite
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Start from the first vertex
    key[0] = 0;
    parent[0] = -1;  // First node is always root of MST

    // MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);  // Pick min key vertex
        mstSet[u] = true;

        // Update key values of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the MST
    printMST(parent, graph);
}

int main() {
    // Example weighted undirected graph (adjacency matrix)
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    // Run Prim’s algorithm
    primMST(graph);

    return 0;
}
