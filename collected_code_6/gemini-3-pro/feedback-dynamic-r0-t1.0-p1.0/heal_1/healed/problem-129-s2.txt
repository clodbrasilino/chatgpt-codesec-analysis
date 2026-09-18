#include <stdio.h>
#include <stdlib.h>

void generateMagicSquare(int n) {
    if (n <= 0 || n % 2 == 0 || n > 999) {
        printf("Magic square is only supported for positive odd integers.\n");
        return;
    }

    int **magicSquare = (int **)malloc((size_t)n * sizeof(int *));
    if (magicSquare == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < n; i++) {
        magicSquare[i] = (int *)calloc((size_t)n, sizeof(int));
        if (magicSquare[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            for (int k = 0; k < i; k++) {
                free(magicSquare[k]);
            }
            free(magicSquare);
            exit(EXIT_FAILURE);
        }
    }

    int i = n / 2;
    int j = n - 1;

    for (int num = 1; num <= n * n; ) {
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

        if (magicSquare[i][j]) {
            j -= 2;
            i++;
            continue;
        } else {
            magicSquare[i][j] = num++;
        }

        j++;
        i--;
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            printf("%3d ", magicSquare[r][c]);
        }
        printf("\n");
    }

    for (int r = 0; r < n; r++) {
        free(magicSquare[r]);
    }
    free(magicSquare);
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    generateMagicSquare(n);

    return EXIT_SUCCESS;
}