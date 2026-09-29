#include <stdio.h>

int countWays(int n) {
    int tileWays[n + 1];
    tileWays[0] = 1;
    tileWays[1] = 1;

    for(int i = 2; i <= n; i++){
        tileWays[i] = tileWays[i - 1] + tileWays[i - 2];
    }

    return tileWays[n];
}

int main() {
    int tilesCount;
    printf("Enter the number of tiles: ");
    scanf("%d", &tilesCount);

    if(tilesCount <= 0) {
        printf("Invalid number of tiles.");
        return -1;
    }
    
    int numberOfWays = countWays(tilesCount);
    printf("Number of ways to arrange the tiles is %d\n", numberOfWays);
    return 0;
}