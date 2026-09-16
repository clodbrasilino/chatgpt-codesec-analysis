#include <stdio.h>
#include <stddef.h>

#define ERR_NULL_PTR -1
#define ERR_DIV_BY_ZERO -2

int list_modulo(const int *a, const int *b, int *result, size_t size) {
    if (a == NULL || b == NULL || result == NULL) {
        return ERR_NULL_PTR;
    }
    if (size == 0) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (b[i] == 0) {
            return ERR_DIV_BY_ZERO;
        }
        result[i] = a[i] % b[i];
    }
    return 0;
}

int main(void) {
    const int a[] = {10, 25, 33, 44, 50};
    const int b[] = {3, 4, 7, 6, 11};
    size_t size = sizeof(a) / sizeof(a[0]);
    int result[sizeof(a) / sizeof(a[0])];
    int ret;

    ret = list_modulo(a, b, result, size);
    if (ret == 0) {
        for (size_t i = 0; i < size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    } else {
        printf("Error calculating modulo\n");
    }

    const int c[] = {10, 20, 30};
    const int d[] = {2, 0, 5};
    int res2[3];

    ret = list_modulo(c, d, res2, 3);
    if (ret == ERR_DIV_BY_ZERO) {
        printf("Division by zero handled\n");
    }

    ret = list_modulo(NULL, b, result, size);
    if (ret == ERR_NULL_PTR) {
        printf("Null pointer handled\n");
    }

    return 0;
}