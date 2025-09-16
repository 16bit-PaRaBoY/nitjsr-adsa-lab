#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6   // Number of vertices in the graph

// Function to find the vertex with minimum distance value
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print the solution
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Dijkstra’s algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];     // Output array: dist[i] = shortest distance from src to i
    bool sptSet[V];  // True if vertex i is included in shortest path tree

    // Initialize distances as infinite and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);  // Pick the min distance vertex not yet processed
        sptSet[u] = true;

        // Update dist[v] only if:
        // 1. v is not in sptSet
        // 2. there is an edge u-v
        // 3. dist[u] + weight(u, v) < dist[v]
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist);
}

// Example usage
int main() {
    // Example graph (adjacency matrix)
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    dijkstra(graph, 0); // Find shortest paths from vertex 0

    return 0;
}
