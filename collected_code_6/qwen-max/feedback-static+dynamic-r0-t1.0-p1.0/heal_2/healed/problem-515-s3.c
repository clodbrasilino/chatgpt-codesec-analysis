#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

bool isSubsetSumDivisible(const int *arr, int n, int m) {
    if (m <= 0 || n <= 0) {
        return false;
    }
    bool table[n + 1][m];
    for (int i = 0; i <= n; i++) {
        table[i][0] = true;
    }
    for (int i = 1; i < m; i++) {
        table[0][i] = false;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[i - 1][j]) {
                table[i][j] = true;
            } else {
                int prev_idx = (j - arr[i - 1] + m) % m;
                if (prev_idx < 0) prev_idx += m;
                table[i][j] = table[i - 1][prev_idx];
            }
        }
    }
    return table[n][0];
}

int main() {
    int arr[MAX_SIZE], n, m;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the divisor m: ");
    scanf("%d", &m);
    if (n > MAX_SIZE || n <= 0) {
        printf("Invalid number of elements.\n");
        return 1;
    }
    if (isSubsetSumDivisible(arr, n, m)) {
        printf("There is a subset with sum divisible by %d.\n", m);
    } else {
        printf("No subset has a sum divisible by %d.\n", m);
    }
    return 0;
}