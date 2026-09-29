#include <stdio.h>
#include <stdlib.h>

void generateMagicSquare(int n) {
    if (n <= 0 || n % 2 == 0) {
        printf("Magic square is only supported for positive odd integers.\n");
        return;
    }

    int **magicSquare = (int **)malloc(n * sizeof(int *));
    if (magicSquare == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        magicSquare[i] = (int *)calloc(n, sizeof(int));
        if (magicSquare[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(magicSquare[j]);
            }
            free(magicSquare);
            return;
        }
    }

    int i = n / 2;
    int j = n - 1;

    for (int num = 1; num <= n * n;) {
        if (i == -1 && j == n) {
            j = n - 2;
            i = 0;
        } else {
            if (j == n) {
                j = 0;
            }
            if (i < 0) {
                i = n - 1;
            }
        }

        if (magicSquare[i][j] != 0) {
            j -= 2;
            i++;
            continue;
        } else {
            magicSquare[i][j] = num++;
        }

        j++;
        i--;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d ", magicSquare[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < n; i++) {
        free(magicSquare[i]);
    }
    free(magicSquare);
}

int main(void) {
    int n;
    
    printf("Enter the size of the magic square (odd integer): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    generateMagicSquare(n);

    return EXIT_SUCCESS;
}