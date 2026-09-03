#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int *modulo_division(const int *a, const int *b, size_t n) {
    if (a == NULL || b == NULL || n == 0) {
        return NULL;
    }
    if (n > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    int *result = malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < n; i++) {
        if (b[i] == 0 || (b[i] == -1 && a[i] == INT_MIN)) {
            free(result);
            return NULL;
        }
        result[i] = a[i] % b[i];
    }
    return result;
}

int main(void) {
    int a[] = {10, 20, 30, 42, INT_MIN};
    int b[] = {3, 7, 4, 5, 1};
    size_t n = sizeof(a) / sizeof(a[0]);

    if (sizeof(b) / sizeof(b[0]) != n) {
        fprintf(stderr, "Lists must have same length\n");
        return EXIT_FAILURE;
    }

    int *r = modulo_division(a, b, n);
    if (r == NULL) {
        fprintf(stderr, "Modulo division failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; i++) {
        printf("%d\n", r[i]);
    }

    free(r);
    return EXIT_SUCCESS;
}