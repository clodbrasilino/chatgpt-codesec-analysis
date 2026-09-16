#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Pair;

Pair *zip_tuples(const int *a, size_t len_a, const int *b, size_t len_b, size_t *out_len) {
    if (a == NULL || b == NULL || out_len == NULL) {
        return NULL;
    }

    size_t n = (len_a < len_b) ? len_a : len_b;
    if (n == 0) {
        *out_len = 0;
        return NULL;
    }

    Pair *result = malloc(n * sizeof(Pair));
    if (result == NULL) {
        *out_len = 0;
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        result[i].first = a[i];
        result[i].second = b[i];
    }

    *out_len = n;
    return result;
}

int main(void) {
    int tuple1[] = {1, 2, 3, 4};
    int tuple2[] = {10, 20, 30, 40};
    /* Possible weaknesses found:
     *  Assignment 'len1=sizeof(tuple1)/sizeof(tuple1[0])', assigned value is 4
     */
    size_t len1 = sizeof(tuple1) / sizeof(tuple1[0]);
    /* Possible weaknesses found:
     *  Assignment 'len2=sizeof(tuple2)/sizeof(tuple2[0])', assigned value is 4
     */
    size_t len2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t zipped_len = 0;

    Pair *zipped = zip_tuples(tuple1, len1, tuple2, len2, &zipped_len);
    if (zipped == NULL) {
        /* Possible weaknesses found:
         *  Condition 'len1==0' is always false [knownConditionTrueFalse]
         *  Condition 'len2==0' is always false [knownConditionTrueFalse]
         *  Condition 'len2==0' is always false
         *  Condition 'len1==0' is always false
         */
        if (zipped_len == 0 && (len1 == 0 || len2 == 0)) {
            printf("Empty result\n");
            return EXIT_SUCCESS;
        }
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