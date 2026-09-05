#include <stdio.h>
#include <stdlib.h>

int** create_pascal_triangle(int n) {
    int** triangle = (int**)malloc((n + 1) * sizeof(int*));
    if (triangle == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= n; i++) {
        triangle[i] = (int*)malloc((i + 1) * sizeof(int));
        if (triangle[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            exit(EXIT_FAILURE);
        }
        triangle[i][0] = 1;
        triangle[i][i] = 1;
        for (int j = 1; j < i; j++) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }
    return triangle;
}

void destroy_pascal_triangle(int** triangle, int n) {
    if (triangle == NULL) {
        return;
    }
    for (int i = 0; i <= n; i++) {
        free(triangle[i]);
    }
    free(triangle);
}

long long sum_of_squares_of_binomial_coefficients(int n) {
    if (n < 0) {
        return 0;
    }
    int** triangle = create_pascal_triangle(n);
    long long sum = 0;
    for (int k = 0; k <= n; k++) {
        long long coeff = triangle[n][k];
        sum += coeff * coeff;
    }
    destroy_pascal_triangle(triangle, n);
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    if (n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return EXIT_FAILURE;
    }
    long long result = sum_of_squares_of_binomial_coefficients(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}