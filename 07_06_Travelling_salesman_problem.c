#include <stdio.h>
#include <limits.h>
#include <time.h>
#define MAX 15  // practical limit for DP TSP

int n;
int dist[MAX][MAX];
int dp[1 << MAX][MAX];

// Recursive DP function
int tsp(int mask, int pos) {
    if (mask == (1 << n) - 1)
        return dist[pos][0]; // return to start

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INT_MAX;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0)
            if (dist[pos][city] != 0)
                ans = (ans < dist[pos][city] + tsp(mask | (1 << city), city)) ?
                      ans : dist[pos][city] + tsp(mask | (1 << city), city);
    }
    return dp[mask][pos] = ans;
}

int main() {
    clock_t start, end;
    double time_taken;

    for (int size = 10; size <= 100; size *= 2) {
        if (size == 60) size = 40; // adjust iteration
        if (size == 100) n = 10;   // realistic DP cap (DP explodes beyond ~15)
        else n = (size > 15) ? 15 : size; // cap to handle runtime

        // Initialize random distances
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = (i == j) ? 0 : (rand() % 20 + 1);

        for (int i = 0; i < (1 << n); i++)
            for (int j = 0; j < n; j++)
                dp[i][j] = -1;

        start = clock();
        int result = tsp(1, 0);
        end = clock();

        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Nodes: %d\tMin Cost: %d\tTime: %.6f sec\n", size, result, time_taken);
    }

    return 0;
}
