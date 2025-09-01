/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <stdio.h>
#include <string.h>

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

void countingSort(int a[], int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) if (a[i] > max) max = a[i];

    int c[max+1]; memset(c, 0, sizeof(c));
    int out[n];

    for (int i = 0; i < n; i++) c[a[i]]++;
    for (int i = 1; i <= max; i++) c[i] += c[i-1];
    for (int i = n-1; i >= 0; i--) out[--c[a[i]]] = a[i];
    for (int i = 0; i < n; i++) a[i] = out[i];
}

int main() {
    int a[] = {4, 2, 2, 8, 3, 3, 1}, n = sizeof(a)/sizeof(a[0]);
    printArray(a, n);
    countingSort(a, n);
    printArray(a, n);
}

