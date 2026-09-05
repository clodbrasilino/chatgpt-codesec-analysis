#include <stdio.h>
#include <stdlib.h>

int* tuple_mod(const int* t1, const int* t2, size_t size) {
    if (t1 == NULL || t2 == NULL || size == 0) {
        return NULL;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        if (t2[i] == 0) {
            free(result);
            return NULL;
        }
        result[i] = t1[i] % t2[i];
    }

    return result;
}

int main(void) {
    const int t1[] = {10, 20, 30, 40, 50};
    const int t2[] = {3, 4, 5, 6, 7};
    size_t size = sizeof(t1) / sizeof(t1[0]);

    int* res = tuple_mod(t1, t2, size);
    if (res == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free(res);

    return EXIT_SUCCESS;
}