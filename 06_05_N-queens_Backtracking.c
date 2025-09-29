#include <stdio.h>
#include <stdbool.h>

#define N 8   // You can change N for different board sizes

// Function to print the solution
void printSolution(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if placing queen at board[row][col] is safe
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    // Check column
    for (i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper-left diagonal
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper-right diagonal
    for (i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Recursive backtracking function
bool solveNQUtil(int board[N][N], int row) {
    if (row >= N) {
        printSolution(board); // Print one valid solution
        return true;
    }

    bool res = false;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1;   // Place queen
            res = solveNQUtil(board, row + 1) || res;
            board[row][col] = 0;   // Backtrack
        }
    }
    return res;
}

// Solve N-Queens problem
void solveNQ() {
    int board[N][N] = {0};

    if (!solveNQUtil(board, 0)) {
        printf("No solution exists\n");
    }
}

int main() {
    solveNQ();
    return 0;
}
