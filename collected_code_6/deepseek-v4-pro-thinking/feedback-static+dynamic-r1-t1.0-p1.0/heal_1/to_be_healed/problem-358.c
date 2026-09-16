#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int *modulo_division(const int *a, const int *b, size_t n) {
    if (a == NULL || b == NULL || n == 0) {
        errno = EINVAL;
        return NULL;
    }
    if (n > (size_t)-1 / sizeof(*a)) {
        errno = ENOMEM;
        return NULL;
    }
    int *result = malloc(n * sizeof(*result));
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    for (size_t i = 0; i < n; ++i) {
        if (b[i] == 0) {
            free(result);
            errno = EDOM;
            return NULL;
        }
        if (b[i] == -1 && a[i] == INT_MIN) {
            free(result);
            errno = ERANGE;
            return NULL;
        }
        result[i] = a[i] % b[i];
    }
    return result;
}

int main(void) {
    int a[] = {10, 20, 30, 40};
    /* Possible weaknesses found:
     *  Variable 'b' can be declared as const array [constVariable]
     */
    int b[] = {3, 7, 5, 9};
    size_t n = sizeof(a) / sizeof(a[0]);
    int *r = modulo_division(a, b, n);
    if (r == NULL) {
        perror("modulo_division failed");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < n; ++i) {
        printf("%d ", r[i]);
    }
    printf("\n");
    free(r);
    return EXIT_SUCCESS;
}