#include <stdio.h>

void generateSquare(int n) {
    int magicSquare[n][n];

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
        if (magicSquare[(int)i][(int)j]) {
            j -= 2;
            i++;
            continue;
        } else
            magicSquare[(int)i][(int)j] = num++;
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