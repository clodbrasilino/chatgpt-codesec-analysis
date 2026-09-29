#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int* generate_spiral_matrix(int n) {
    if (n <= 0 || n > 46340) {
        return NULL;
    }

    size_t size = (size_t)n * (size_t)n;
    int *matrix = (int*)malloc(size * sizeof(int));
    if (matrix == NULL) {
        return NULL;
    }

    int val = 1;
    int top = 0;
    int bottom = n - 1;
    int left = 0;
    int right = n - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; ++i) {
            matrix[top * n + i] = val++;
        }
        top++;

        for (int i = top; i <= bottom; ++i) {
            matrix[i * n + right] = val++;
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; --i) {
                matrix[bottom * n + i] = val++;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                matrix[i * n + left] = val++;
            }
            left++;
        }
    }

    return matrix;
}

void print_matrix(const int *matrix, int n) {
    if (matrix == NULL || n <= 0) {
        return;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d ", matrix[i * n + j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long n_long = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || n_long <= 0 || n_long > 46340) {
        fprintf(stderr, "Invalid input for n. Must be an integer between 1 and 46340.\n");
        return 1;
    }

    int n = (int)n_long;
    int *matrix = generate_spiral_matrix(n);
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid size.\n");
        return 1;
    }

    print_matrix(matrix, n);

    free(matrix);
    return 0;
}