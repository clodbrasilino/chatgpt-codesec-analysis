#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef enum {
    ZIP_OK,
    ZIP_EMPTY,
    ZIP_BAD_ARGS,
    ZIP_NO_MEMORY
} ZipStatus;

ZipStatus zip_tuples(const int *a, size_t len_a, const int *b, size_t len_b,
                     Pair **out, size_t *out_len) {
    if (a == NULL || b == NULL || out == NULL || out_len == NULL) {
        return ZIP_BAD_ARGS;
    }

    *out = NULL;
    *out_len = 0;

    size_t n = (len_a < len_b) ? len_a : len_b;
    if (n == 0) {
        return ZIP_EMPTY;
    }

    Pair *result = malloc(n * sizeof(Pair));
    if (result == NULL) {
        return ZIP_NO_MEMORY;
    }

    for (size_t i = 0; i < n; i++) {
        result[i].first = a[i];
        result[i].second = b[i];
    }

    *out = result;
    *out_len = n;
    return ZIP_OK;
}

int main(void) {
    int tuple1[] = {1, 2, 3, 4};
    int tuple2[] = {10, 20, 30, 40};
    size_t len1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t len2 = sizeof(tuple2) / sizeof(tuple2[0]);

    Pair *zipped = NULL;
    size_t zipped_len = 0;

    ZipStatus status = zip_tuples(tuple1, len1, tuple2, len2, &zipped, &zipped_len);

    if (status == ZIP_EMPTY) {
        printf("Empty result\n");
        return EXIT_SUCCESS;
    }
    if (status != ZIP_OK) {
        fprintf(stderr, "Failed to zip tuples\n");
        return EXIT_FAILURE;
    }

    printf("[");
    for (size_t i = 0; i < zipped_len; i++) {
        printf("(%d, %d)", zipped[i].first, zipped[i].second);
        if (i + 1 < zipped_len) {
            printf(", ");
        }
    }
    printf("]\n");

    free(zipped);
    return EXIT_SUCCESS;
}