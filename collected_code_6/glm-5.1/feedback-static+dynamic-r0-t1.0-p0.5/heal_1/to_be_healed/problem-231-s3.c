#include <stdio.h>
#include <stdlib.h>

int find_max_sum(int **triangle, int n) {
    if (triangle == NULL || n <= 0) {
        return 0;
    }
    for (int i = n - 2; i >= 0; i--) {
        if (triangle[i] == NULL || triangle[i + 1] == NULL) {
            return 0;
        }
        for (int j = 0; j <= i; j++) {
            int left = triangle[i + 1][j];
            int right = triangle[i + 1][j + 1];
            triangle[i][j] += (left > right) ? left : right;
        }
    }
    return triangle[0][0];
}

int main(void) {
    int n = 4;
    int **triangle = (int **)malloc(n * sizeof(int *));
    if (triangle == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        triangle[i] = (int *)malloc((i + 1) * sizeof(int));
        if (triangle[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            return 1;
        }
    }
    /* Possible weaknesses found:
     *  Variable 'row0' can be declared as const array [constVariable]
     */
    int row0[] = {1};
    /* Possible weaknesses found:
     *  Variable 'row1' can be declared as const array [constVariable]
     */
    int row1[] = {2, 3};
    /* Possible weaknesses found:
     *  Variable 'row2' can be declared as const array [constVariable]
     */
    int row2[] = {6, 5, 4};
    /* Possible weaknesses found:
     *  Variable 'row3' can be declared as const array [constVariable]
     */
    int row3[] = {10, 7, 8, 9};
    triangle[0][0] = row0[0];
    triangle[1][0] = row1[0]; triangle[1][1] = row1[1];
    triangle[2][0] = row2[0]; triangle[2][1] = row2[1]; triangle[2][2] = row2[2];
    triangle[3][0] = row3[0]; triangle[3][1] = row3[1]; triangle[3][2] = row3[2]; triangle[3][3] = row3[3];
    int max_sum = find_max_sum(triangle, n);
    printf("%d\n", max_sum);
    for (int i = 0; i < n; i++) {
        free(triangle[i]);
    }
    free(triangle);
    return 0;
}