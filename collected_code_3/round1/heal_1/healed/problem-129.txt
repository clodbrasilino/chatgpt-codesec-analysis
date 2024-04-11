#include <stdio.h>
#include <string.h>

void generateSquare(int n) {
    int magicSquare[n][n];

    // initialize magicSquare to zero
    memset(magicSquare, 0, sizeof(magicSquare));

    int i = n / 2;
    int j = n - 1;

    for (int num = 1; num <= n * n;) {
        if (i == -1 && j == n) {
            j = n - 2;
            i = 0;
        } else {
            if (j == n)
                j = 0;
            if (i < 0)
                i = n - 1;
        }
        
        if (magicSquare[i][j]) {
            j -= 2;
            i++;
            continue;
        } else
            magicSquare[i][j] = num++;
        j++;
        i--;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%3d ", magicSquare[i][j]);
        printf("\n");
    }
}

int main() {
    int n = 3;
    generateSquare(n);
    return 0;
}