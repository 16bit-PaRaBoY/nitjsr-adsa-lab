#include <stdio.h>

void findMinCoins(int coins[], int n, int amount) {
    printf("Coins used:\n");
    for (int i = 0; i < n; i++) {
        int count = amount / coins[i];
        if (count != 0) {
            printf("%d x %d\n", coins[i], count);
            amount -= count * coins[i];
        }
    }
}

int main() {
    int coins[] = {10, 5, 2, 1};
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount;

    printf("Enter the amount: ");
    scanf("%d", &amount);

    findMinCoins(coins, n, amount);
    return 0;
}
