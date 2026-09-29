#include <stdio.h>
#include <stdlib.h>

int count_digits(int num) {
    int count = 0;
    if (num == 0) return 1;
    if (num < 0) num = -num;
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

int total_digits(int a, int b) {
    return count_digits(a) + count_digits(b);
}

void sort_tuples(int **tuples, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (total_digits(tuples[j][0], tuples[j][1]) > 
                total_digits(tuples[j + 1][0], tuples[j + 1][1])) {
                int temp0 = tuples[j][0];
                int temp1 = tuples[j][1];
                tuples[j][0] = tuples[j + 1][0];
                tuples[j][1] = tuples[j + 1][1];
                tuples[j + 1][0] = temp0;
                tuples[j + 1][1] = temp1;
            }
        }
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n <= 0) {
        return 1;
    }

    int **tuples = (int **)malloc((size_t)n * sizeof(int *));
    if (tuples == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        tuples[i] = (int *)malloc(2 * sizeof(int));
        if (tuples[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(tuples[j]);
            }
            free(tuples);
            return 1;
        }
        if (scanf("%d %d", &tuples[i][0], &tuples[i][1]) != 2) {
            for (int j = 0; j <= i; j++) {
                free(tuples[j]);
            }
            free(tuples);
            return 1;
        }
    }

    sort_tuples(tuples, n);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", tuples[i][0], tuples[i][1]);
    }

    for (int i = 0; i < n; i++) {
        free(tuples[i]);
    }
    free(tuples);

    return 0;
}