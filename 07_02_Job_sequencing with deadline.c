#include <stdio.h>
#include <stdlib.h>

struct Job {
    char id;
    int deadline;
    int profit;
};

// Comparator for sorting jobs by profit (descending)
int compare(const void *a, const void *b) {
    return ((struct Job*)b)->profit - ((struct Job*)a)->profit;
}

void jobSequencing(struct Job jobs[], int n) {
    qsort(jobs, n, sizeof(struct Job), compare);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;

    int slot[maxDeadline];
    char result[maxDeadline];
    for (int i = 0; i < maxDeadline; i++) slot[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i;
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    printf("Job sequence for maximum profit: ");
    for (int i = 0; i < maxDeadline; i++)
        if (slot[i] != -1)
            printf("%c ", result[i]);
}

int main() {
    struct Job jobs[] = {
        {'A', 2, 100}, {'B', 1, 19}, {'C', 2, 27},
        {'D', 1, 25}, {'E', 3, 15}
    };
    int n = sizeof(jobs) / sizeof(jobs[0]);
    jobSequencing(jobs, n);
    return 0;
}
