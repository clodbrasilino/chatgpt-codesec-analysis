#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

void generate_magic_square(int **matrix, int n) {
    if (matrix == NULL || n <= 0) {
        return;
    }
    
    int num = 1;
    int row = 0;
    int col = n / 2;
    
    while (num <= n * n) {
        if (row == -1 && col == n) {
            row = 1;
            col = n - 1;
        } else {
            if (col == n) {
                col = 0;
            }
            if (row == -1) {
                row = n - 1;
            }
        }
        
        if (matrix[row][col] != 0) {
            row += 2;
            col -= 1;
            
            if (row >= n) {
                row -= n;
            }
            if (col < 0) {
                col += n;
            }
        }
        
        matrix[row][col] = num;
        num++;
        
        row--;
        col++;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <odd_size>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    
    if (errno == ERANGE || endptr == argv[1] || *endptr != '\0' || val <= 0 || val > INT_MAX) {
        fprintf(stderr, "Error: Size must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    
    if (n % 2 == 0) {
        fprintf(stderr, "Error: Size must be an odd integer.\n");
        return EXIT_FAILURE;
    }
    
    int **matrix = (int **)malloc(n * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)calloc(n, sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return EXIT_FAILURE;
        }
    }
    
    generate_magic_square(matrix, n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return EXIT_SUCCESS;
}