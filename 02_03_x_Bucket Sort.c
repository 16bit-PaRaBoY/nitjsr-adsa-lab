/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <stdio.h>

void printArray(int a[], int n){ for(int i=0;i<n;i++) printf("%d ",a[i]); printf("\n"); }

void insertionSort(int a[], int n){
    for(int i=1;i<n;i++){ int key=a[i],j=i-1;
        while(j>=0 && a[j]>key) a[j+1]=a[j--];
        a[j+1]=key;
    }
}

void bucketSort(int a[], int n){
    int b[10][n], sz[10]={0};
    for(int i=0;i<n;i++) b[a[i]/10][sz[a[i]/10]++]=a[i];
    for(int i=0;i<10;i++) insertionSort(b[i],sz[i]);
    
    int k=0; for(int i=0;i<10;i++) 
        for(int j=0;j<sz[i];j++) a[k++]=b[i][j];
}

int main(){
    int a[]={42,32,33,52,37,47,51},n=sizeof(a)/sizeof(a[0]);
    printArray(a,n); bucketSort(a,n); printArray(a,n);
}
