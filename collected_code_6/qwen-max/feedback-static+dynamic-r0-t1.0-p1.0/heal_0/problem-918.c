#include <stdio.h>
#include <stdlib.h>

int count_change(int amount, int denominations[], int n) {
    int *table = (int *)malloc((amount + 1) * sizeof(int));
    if (!table) return -1;
    for (int i = 0; i <= amount; i++) table[i] = 0;
    table[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = denominations[i]; j <= amount; j++) {
            table[j] += table[j - denominations[i]];
        }
    }

    int result = table[amount];
    free(table);
    return result;
}

int main() {
    int amount = 5;
    int denominations[] = {1, 2, 5};
    int n = 3;

    int result = count_change(amount, denominations, n);
    if (result == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Number of ways to make change: %d\n", result);
    return 0;
}