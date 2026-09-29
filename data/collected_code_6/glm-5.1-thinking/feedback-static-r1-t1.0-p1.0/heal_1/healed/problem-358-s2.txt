#include <stdio.h>
#include <stdlib.h>

int* list_modulo(const int* a, const int* b, size_t size) {
    if (a == NULL || b == NULL || size == 0) {
        return NULL;
    }

    int* result = malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        if (b[i] == 0) {
            free(result);
            return NULL;
        }
        result[i] = a[i] % b[i];
    }

    return result;
}

int main(void) {
    const int a[] = {10, 25, 31, 44, 50};
    const int b[] = {3, 4, 7, 5, 8};
    size_t size = sizeof(a) / sizeof(a[0]);

    const int* result = list_modulo(a, b, size);
    if (result != NULL) {
        for (size_t i = 0; i < size; ++i) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free((void*)result);
    } else {
        printf("Failed to compute modulo.\n");
    }

    const int c[] = {10, 20, 30};
    const int d[] = {1, 0, 3};
    size_t size2 = sizeof(c) / sizeof(c[0]);

    const int* result2 = list_modulo(c, d, size2);
    if (result2 == NULL) {
        printf("Zero divisor handled correctly.\n");
    }

    return 0;
}