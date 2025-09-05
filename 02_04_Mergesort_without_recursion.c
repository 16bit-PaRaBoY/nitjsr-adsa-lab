#include <stdio.h>
#include <stdlib.h>

// Function to merge two sorted halves
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Structure to simulate recursion stack frame
typedef struct {
    int left, right, processed;
} Frame;

void mergeSortIterative(int arr[], int n) {
    Frame *stack = (Frame*)malloc(n * sizeof(Frame));
    int top = -1;

    // Push the initial range
    stack[++top] = (Frame){0, n - 1, 0};

    while (top >= 0) {
        Frame curr = stack[top--];

        int l = curr.left, r = curr.right;

        if (l >= r) continue; // Single element, already sorted

        if (curr.processed == 0) {
            int mid = (l + r) / 2;

            // Push current frame again, marked as "to be merged"
            stack[++top] = (Frame){l, r, 1};

            // Push right and left halves (divide step)
            stack[++top] = (Frame){mid + 1, r, 0};
            stack[++top] = (Frame){l, mid, 0};
        } else {
            // Merge step
            int mid = (l + r) / 2;
            merge(arr, l, mid, r);
        }
    }

    free(stack);
}

// Driver code
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    mergeSortIterative(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
