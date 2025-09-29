#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

// Direction vectors for moves (row, col)
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

// Structure to represent a puzzle node
struct Node {
    int mat[N][N];
    int x, y;      // Blank tile coordinates
    int cost;      // Heuristic cost
    int level;     // Depth (g(x))
    struct Node* parent;
};

// Function to allocate a new node
struct Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, struct Node* parent) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    memcpy(node->mat, mat, sizeof(node->mat));

    // Swap blank tile with new coordinates
    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->cost = 0;
    node->level = level;
    node->parent = parent;

    return node;
}

// Calculate Manhattan distance as heuristic
int calculateCost(int mat[N][N], int final[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] && mat[i][j] != final[i][j]) {
                int val = mat[i][j];
                int targetRow = (val - 1) / N;
                int targetCol = (val - 1) % N;
                cost += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }
    return cost;
}

// Print matrix
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == 0)
                printf("   ");
            else
                printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Priority Queue node
struct PQNode {
    struct Node* node;
    int priority;
};

// Min-heap for branch and bound
#define MAX 100000
struct PQNode heap[MAX];
int heapSize = 0;

void push(struct Node* node, int priority) {
    int i = heapSize++;
    heap[i].node = node;
    heap[i].priority = priority;
    while (i && heap[(i - 1) / 2].priority > heap[i].priority) {
        struct PQNode temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

struct Node* pop() {
    struct Node* top = heap[0].node;
    heap[0] = heap[--heapSize];
    int i = 0;
    while (2 * i + 1 < heapSize) {
        int smallest = i;
        if (heap[2 * i + 1].priority < heap[smallest].priority)
            smallest = 2 * i + 1;
        if (2 * i + 2 < heapSize && heap[2 * i + 2].priority < heap[smallest].priority)
            smallest = 2 * i + 2;
        if (smallest == i) break;
        struct PQNode temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        i = smallest;
    }
    return top;
}

// Check if coordinates are valid
int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Print path from root to goal
void printPath(struct Node* root) {
    if (root == NULL) return;
    printPath(root->parent);
    printMatrix(root->mat);
}

// Solve puzzle using Branch and Bound
void solve(int initial[N][N], int x, int y, int final[N][N]) {
    struct Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);

    push(root, root->cost);

    while (heapSize) {
        struct Node* min = pop();

        if (min->cost == 0) {
            printf("Solution found in %d moves:\n", min->level);
            printPath(min);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (isSafe(newX, newY)) {
                struct Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateCost(child->mat, final);
                push(child, child->cost + child->level);
            }
        }
    }
}

int main() {
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };

    int final[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };

    int x = 1, y = 2; // Blank tile position in initial state

    solve(initial, x, y, final);

    return 0;
}
