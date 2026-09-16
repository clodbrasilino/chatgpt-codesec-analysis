#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_occurring_divisor(int a, int b) {
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    if (b < 1) return 0;

    int size = b + 1;
    int *count = (int *)calloc(size, sizeof(int));
    if (count == NULL) return -1;

    for (int i = a; i <= b; i++) {
        for (int d = 1; d <= i; d++) {
            if (i % d == 0) {
                count[d]++;
            }
        }
    }

    int max_count = 0;
    int max_divisor = 0;
    for (int d = 1; d <= b; d++) {
        if (count[d] > max_count) {
            max_count = count[d];
            max_divisor = d;
        }
    }

    free(count);
    return max_divisor;
}

int main(void) {
    int a = 10;
    int b = 20;
    int result = max_occurring_divisor(a, b);
    if (result == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Maximum occurring divisor in [%d, %d]: %d\n", a, b, result);

    int c = 1;
    int d = 10;
    result = max_occurring_divisor(c, d);
    if (result == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Maximum occurring divisor in [%d, %d]: %d\n", c, d, result);

    int e = 100;
    int f = 100;
    result = max_occurring_divisor(e, f);
    if (result == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Maximum occurring divisor in [%d, %d]: %d\n", e, f, result);

    return 0;
}