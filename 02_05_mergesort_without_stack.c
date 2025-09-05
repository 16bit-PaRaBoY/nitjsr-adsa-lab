#include <stdio.h>
#include <stdlib.h>

// Merge two sorted subarrays: arr[l..m] and arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Iterative bottom-up merge sort
void mergeSort(int arr[], int n) {
    int currSize, leftStart;

    // currSize = size of subarrays to be merged
    for (currSize = 1; currSize < n; currSize = 2 * currSize) {
        // Pick starting point of left subarray
        for (leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
            int mid = leftStart + currSize - 1;
            int rightEnd = (leftStart + 2 * currSize - 1 < n - 1) ?
                           (leftStart + 2 * currSize - 1) : (n - 1);

            if (mid < rightEnd)  // Ensure valid merge
                merge(arr, leftStart, mid, rightEnd);
        }
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Unsorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);

    mergeSort(arr, n);

    printf("\nSorted array:   ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);

    return 0;
}
