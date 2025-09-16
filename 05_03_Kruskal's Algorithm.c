#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
typedef struct {
    int src, dest, weight;
} Edge;

// Structure to represent a subset for union-find
typedef struct {
    int parent;
    int rank;
} Subset;

// Compare function for qsort (sort edges by weight)
int compareEdges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;
}

// Find set of an element i (uses path compression)
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two sets (by rank)
void unionSets(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Kruskal's algorithm
void KruskalMST(Edge edges[], int V, int E) {
    Edge result[V]; // Store MST edges
    int e = 0;      // Index for result[]
    int i = 0;      // Index for sorted edges

    // Sort all edges by weight
    qsort(edges, E, sizeof(Edge), compareEdges);

    // Allocate memory for subsets
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Keep picking edges until MST has (V-1) edges
    while (e < V - 1 && i < E) {
        Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge doesn’t cause cycle, add it to MST
        if (x != y) {
            result[e++] = next_edge;
            unionSets(subsets, x, y);
        }
    }

    // Print the MST
    printf("Edge \tWeight\n");
    int minCost = 0;
    for (i = 0; i < e; i++) {
        printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
        minCost += result[i].weight;
    }
    printf("Minimum Cost of MST = %d\n", minCost);

    free(subsets);
}

// Example usage
int main() {
    int V = 4;  // Number of vertices
    int E = 5;  // Number of edges

    Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    KruskalMST(edges, V, E);

    return 0;
}
