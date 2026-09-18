#include <stdio.h>
#include <stdlib.h>

void generateMagicSquare(int n) {
    if (n % 2 == 0 || n <= 0 || n > 999) {
        printf("Magic square generation is only supported for positive odd integers.\n");
        return;
    }

    int **magicSquare = (int **)malloc(n * sizeof(int *));
    if (magicSquare == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        magicSquare[i] = (int *)calloc(n, sizeof(int));
        if (magicSquare[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(magicSquare[j]);
            }
            free(magicSquare);
            exit(EXIT_FAILURE);
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