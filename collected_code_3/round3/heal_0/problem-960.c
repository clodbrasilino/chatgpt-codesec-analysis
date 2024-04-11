#include <stdio.h>

int tiling(int n) {
    int tile[n+1];
    tile[0] = 0;
    tile[1] = 1;
    tile[2] = 2;

    for (int i = 3; i <= n; i++) {
        tile[i] = tile[i-1] + tile[i-2];
    }

    return tile[n];
}

int main() {
    int n;
    printf("Enter the number of tiles: ");
    scanf("%d", &n);
    printf("Number of ways: %d\n", tiling(n));
    return 0;
}