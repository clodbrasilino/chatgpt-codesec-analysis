#include <stdio.h>

#define MAX 100

int lookup[MAX][MAX];

int countSeq(int n, int m) {
    if (n == 0)
        return 1;
    if (m == 0)
        return 0;
    if (lookup[n][m] != -1)
        return lookup[n][m];
    int count = 0;
    for (int i = m; i > 0; i--)
        count += countSeq(n - 1, i / 2);
    lookup[n][m] = count;
    return count;
}

void initializeLookup() {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            lookup[i][j] = -1;
}

int main() {
    int n, m;
    printf("Enter the length of the sequence: ");
    scanf("%d", &n);
    printf("Enter the maximum value: ");
    scanf("%d", &m);
    initializeLookup();
    printf("Number of possible sequences: %d\n", countSeq(n, m));
    return 0;
}