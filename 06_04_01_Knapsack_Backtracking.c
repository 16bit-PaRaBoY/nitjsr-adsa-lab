#include <stdio.h>

// Global variables to store best solution
int maxValue = 0;
int bestSet[100];
int currentSet[100];

// Recursive backtracking function
void knapSackBT(int i, int n, int W, int wt[], int val[], int currWeight, int currValue) {
    if (i == n) {
        // Reached end, check if better solution found
        if (currValue > maxValue) {
            maxValue = currValue;
            for (int k = 0; k < n; k++)
                bestSet[k] = currentSet[k];
        }
        return;
    }

    // Choice 1: Exclude item i
    currentSet[i] = 0;
    knapSackBT(i + 1, n, W, wt, val, currWeight, currValue);

    // Choice 2: Include item i (if it fits)
    if (currWeight + wt[i] <= W) {
        currentSet[i] = 1;
        knapSackBT(i + 1, n, W, wt, val, currWeight + wt[i], currValue + val[i]);
    }
}

int main() {
    int val[] = {60, 100, 120};
    int wt[]  = {10, 20, 30};
    int W = 50;   // Knapsack capacity
    int n = sizeof(val) / sizeof(val[0]);

    // Initialize best solution
    for (int i = 0; i < n; i++)
        bestSet[i] = 0;

    // Solve knapsack using backtracking
    knapSackBT(0, n, W, wt, val, 0, 0);

    // Print result
    printf("Maximum value in Knapsack = %d\n", maxValue);
    printf("Items included (1 = taken, 0 = not taken): ");
    for (int i = 0; i < n; i++)
        printf("%d ", bestSet[i]);
    printf("\n");

    return 0;
}
