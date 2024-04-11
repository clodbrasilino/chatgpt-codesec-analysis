#include <stdio.h>

int tileCount(int n) {
    int tileWays[n + 1];
    tileWays[0] = 1;
    tileWays[1] = 1;

    for (int i = 2; i <= n; i++) {
        tileWays[i] = tileWays[i - 1] + tileWays[i - 2];
    }

    return tileWays[n];
}

int main() {
    int n;
    printf("Enter the length of the floor: ");
    scanf("%d", &n);
    printf("Number of ways to tile the floor: %d\n", tileCount(n));
    return 0;
}