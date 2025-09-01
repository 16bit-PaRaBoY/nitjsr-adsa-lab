/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <stdio.h>

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

void countSort(int a[], int n, int exp) {
    int out[n], c[10] = {0};
    for (int i = 0; i < n; i++) c[(a[i]/exp)%10]++;
    for (int i = 1; i < 10; i++) c[i] += c[i-1];
    for (int i = n-1; i >= 0; i--) out[--c[(a[i]/exp)%10]] = a[i];
    for (int i = 0; i < n; i++) a[i] = out[i];
}

void radixSort(int a[], int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) if (a[i] > max) max = a[i];
    for (int exp = 1; max/exp > 0; exp *= 10) countSort(a, n, exp);
}

int main() {
    int a[] = {170, 45, 75, 90, 802, 24, 2, 66}, n = sizeof(a)/sizeof(a[0]);
    printArray(a, n);
    radixSort(a, n);
    printArray(a, n);
}

