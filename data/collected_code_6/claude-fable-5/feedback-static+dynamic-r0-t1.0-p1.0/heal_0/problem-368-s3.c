#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *repeat_tuple(const int *tuple, size_t tuple_len, size_t n, size_t *out_len)
{
    if (tuple == NULL || out_len == NULL || tuple_len == 0 || n == 0) {
        return NULL;
    }

    if (tuple_len > SIZE_MAX / n) {
        return NULL;
    }

    size_t total = tuple_len * n;

    if (total > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *result = malloc(total * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < tuple_len; j++) {
            result[i * tuple_len + j] = tuple[j];
        }
    }

    *out_len = total;
    return result;
}

int main(void)
{
    int tuple[] = {1, 2, 3};
    size_t tuple_len = sizeof(tuple) / sizeof(tuple[0]);
    size_t n = 4;
    size_t result_len = 0;

    int *result = repeat_tuple(tuple, tuple_len, n, &result_len);
    if (result == NULL) {
        fprintf(stderr, "Failed to repeat tuple\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (size_t i = 0; i < result_len; i++) {
        printf("%d", result[i]);
        if (i + 1 < result_len) {
            printf(", ");
        }
    }
    printf(")\n");

    free(result);
    return EXIT_SUCCESS;
}