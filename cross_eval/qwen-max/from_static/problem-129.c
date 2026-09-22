#include <stdio.h>
#include <stdlib.h>

void fillMagicSquare(int square[][10], int n) {
    int num = 1;
    int i = n / 2;
    int j = n - 1;

    while (num <= n * n) {
        if (i == -1 && j == n) {
            i = 0;
            j = n - 2;
        }
        if (j == n) {
            j = 0;
        }
        if (i < 0) {
            i = n - 1;
        }

        if (square[i][j] != 0) {
            j -= 2;
            i++;
            continue;
        } else {
            square[i][j] = num;
            num++;
        }
        i--;
        j++;
    }
}

int main() {
    int n;
    printf("Enter the size of the magic square (odd number): ");
    if (scanf("%d", &n) != 1 || n % 2 == 0 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter an odd positive integer.\n");
        return EXIT_FAILURE;
    }

    int square[10][10];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            square[i][j] = 0;
        }
    }

    fillMagicSquare(square, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d ", square[i][j]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}