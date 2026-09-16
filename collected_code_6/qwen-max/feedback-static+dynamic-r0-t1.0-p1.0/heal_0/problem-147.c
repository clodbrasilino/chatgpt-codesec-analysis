#include <stdio.h>
#include <stdlib.h>

int** allocate_triangle(int n) {
    int **triangle = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        triangle[i] = (int*)malloc((i + 1) * sizeof(int));
    }
    return triangle;
}

void free_triangle(int **triangle, int n) {
    for (int i = 0; i < n; ++i) {
        free(triangle[i]);
    }
    free(triangle);
}

int find_max_path_sum(int **triangle, int n) {
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            triangle[i][j] += (triangle[i + 1][j] > triangle[i + 1][j + 1]) ? triangle[i + 1][j] : triangle[i + 1][j + 1];
        }
    }
    return triangle[0][0];
}

int main() {
    int n = 4;
    int **triangle = allocate_triangle(n);

    triangle[0][0] = 3;
    triangle[1][0] = 7; triangle[1][1] = 4;
    triangle[2][0] = 2; triangle[2][1] = 4; triangle[2][2] = 6;
    triangle[3][0] = 8; triangle[3][1] = 5; triangle[3][2] = 9; triangle[3][3] = 3;

    int max_sum = find_max_path_sum(triangle, n);
    printf("%d\n", max_sum);

    free_triangle(triangle, n);
    return 0;
}