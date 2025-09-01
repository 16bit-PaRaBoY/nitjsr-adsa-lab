/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <stdio.h>

void printArray(int a[], int n){ for(int i=0;i<n;i++) printf("%d ",a[i]); printf("\n"); }

void radixExchangeSort(int a[], int left, int right, int bit){
    if (left >= right || bit < 0) return;
    int i = left, j = right;
    while (i <= j) {
        while (i <= j && ((a[i] >> bit) & 1) == 0) i++;
        while (i <= j && ((a[j] >> bit) & 1) == 1) j--;
        if (i < j){ int t=a[i]; a[i]=a[j]; a[j]=t; }
    }
    radixExchangeSort(a, left, j, bit-1);
    radixExchangeSort(a, i, right, bit-1);
}

int main(){
    int a[] = {53, 3, 542, 748, 14, 214};
    int n = sizeof(a)/sizeof(a[0]);
    printArray(a,n);
    radixExchangeSort(a,0,n-1,31); // start with MSB (31 for 32-bit int)
    printArray(a,n);
}
