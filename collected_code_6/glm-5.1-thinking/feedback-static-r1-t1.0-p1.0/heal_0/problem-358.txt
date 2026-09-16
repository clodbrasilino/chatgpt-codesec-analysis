#include <stdio.h>
#include <stddef.h>

int list_modulo(const int *a, const int *b, int *result, size_t length) {
    if (a == NULL || b == NULL || result == NULL || length == 0) {
        return -1;
    }

    for (size_t i = 0; i < length; i++) {
        if (b[i] == 0) {
            return -1;
        }
        result[i] = a[i] % b[i];
    }

    return 0;
}

int main(void) {
    int a[] = {10, 25, 31, 44, 50};
    int b[] = {3, 4, 7, 5, 6};
    size_t length = sizeof(a) / sizeof(a[0]);
    int result[5];

    if (list_modulo(a, b, result, length) == 0) {
        for (size_t i = 0; i < length; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    } else {
        printf("Error\n");
    }

    return 0;
}