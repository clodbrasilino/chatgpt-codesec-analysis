#include <stdio.h>
#include <stdlib.h>

int *interleave(const int *list1, const int *list2, size_t len) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }

    if (len == 0) {
        return NULL;
    }

    int *result = malloc(len * 2 * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        result[i * 2] = list1[i];
        result[i * 2 + 1] = list2[i];
    }

    return result;
}

int main(void) {
    const int list1[] = {1, 2, 3};
    const int list2[] = {4, 5, 6};
    size_t len = sizeof(list1) / sizeof(list1[0]);

    int *interleaved = interleave(list1, list2, len);
    if (interleaved == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < len * 2; i++) {
        printf("%d ", interleaved[i]);
    }
    printf("\n");

    free(interleaved);
    interleaved = NULL;

    return EXIT_SUCCESS;
}