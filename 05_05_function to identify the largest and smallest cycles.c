#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20

int graph[MAX][MAX];    // adjacency matrix
bool visited[MAX];
int stack[MAX];
int V;                  // number of vertices
int top = -1;

int smallestCycle = MAX;
int largestCycle = -1;

// Utility: print a cycle
void printCycle(int start) {
    printf("Cycle: ");
    for (int i = start; i <= top; i++)
        printf("%d ", stack[i]);
    printf("%d\n", stack[start]); // repeat start to close cycle
}

// DFS backtracking to find cycles
void DFS(int u, int parent) {
    visited[u] = true;
    stack[++top] = u;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            // If v is not visited, recurse
            if (!visited[v]) {
                DFS(v, u);
            }
            // If v is visited and is on current stack → cycle found
            else {
                // find cycle length
                int cycleLen = 0, startIndex = -1;
                for (int i = 0; i <= top; i++) {
                    if (stack[i] == v) {
                        startIndex = i;
                        cycleLen = top - i + 1;
                        break;
                    }
                }
                if (startIndex != -1 && cycleLen > 1) {
                    // Update smallest and largest
                    if (cycleLen < smallestCycle)
                        smallestCycle = cycleLen;
                    if (cycleLen > largestCycle)
                        largestCycle = cycleLen;

                    // Print cycle (optional)
                    printCycle(startIndex);
                }
            }
        }
    }

    // backtrack
    visited[u] = false;
    top--;
}

void findCycles() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            visited[j] = false;
        DFS(i, -1);
    }

    if (smallestCycle == MAX)
        printf("No cycles found.\n");
    else {
        printf("Smallest Cycle Length = %d\n", smallestCycle);
        printf("Largest Cycle Length = %d\n", largestCycle);
    }
}

int main() {
    V = 6;
    // Example graph (undirected, add edges both ways)
    graph[0][1] = graph[1][0] = 1;
    graph[1][2] = graph[2][1] = 1;
    graph[2][0] = graph[0][2] = 1; // cycle 0-1-2

    graph[2][3] = graph[3][2] = 1;
    graph[3][4] = graph[4][3] = 1;
    graph[4][5] = graph[5][4] = 1;
    graph[5][2] = graph[2][5] = 1; // cycle 2-3-4-5

    findCycles();

    return 0;
}
