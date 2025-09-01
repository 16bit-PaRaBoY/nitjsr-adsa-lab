/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

// Address Calculation Sort (Hash Sort)
void addressCalculationSort(int a[], int n, int maxVal) {
    int *table = (int*)calloc(maxVal+1, sizeof(int));

    // Hashing: count occurrences
    for (int i = 0; i < n; i++) table[a[i]]++;

    // Reconstruct sorted array
    int k = 0;
    for (int i = 0; i <= maxVal; i++)
        while (table[i]--) a[k++] = i;

    free(table);
}

int main() {
    int a[] = {29, 25, 3, 49, 9, 37, 21, 43};
    int n = sizeof(a)/sizeof(a[0]);
    int maxVal = 50; // must know max value (range of keys)

    printf("Original: "); printArray(a, n);
    addressCalculationSort(a, n, maxVal);
    printf("Sorted:   "); printArray(a, n);
}
