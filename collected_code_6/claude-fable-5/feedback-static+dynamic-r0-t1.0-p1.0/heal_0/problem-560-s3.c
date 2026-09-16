#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static int *tuple_union(const int *first, size_t first_len,
                        const int *second, size_t second_len,
                        size_t *result_len)
{
    int *combined = NULL;
    int *result = NULL;
    size_t total = 0;
    size_t i = 0;
    size_t count = 0;

    if (first == NULL || second == NULL || result_len == NULL) {
        return NULL;
    }

    total = first_len + second_len;
    if (total < first_len) {
        return NULL;
    }
    if (total == 0) {
        *result_len = 0;
        return NULL;
    }

    combined = malloc(total * sizeof(int));
    if (combined == NULL) {
        return NULL;
    }

    for (i = 0; i < first_len; i++) {
        combined[i] = first[i];
    }
    for (i = 0; i < second_len; i++) {
        combined[first_len + i] = second[i];
    }

    qsort(combined, total, sizeof(int), compare_ints);

    count = 1;
    for (i = 1; i < total; i++) {
        if (combined[i] != combined[i - 1]) {
            count++;
        }
    }

    result = malloc(count * sizeof(int));
    if (result == NULL) {
        free(combined);
        return NULL;
    }

    result[0] = combined[0];
    count = 1;
    for (i = 1; i < total; i++) {
        if (combined[i] != combined[i - 1]) {
            result[count] = combined[i];
            count++;
        }
    }

    free(combined);
    *result_len = count;
    return result;
}

int main(void)
{
    int tuple1[] = {3, 4, 5, 6};
    int tuple2[] = {5, 7, 4, 10};
    size_t len1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t len2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t union_len = 0;
    size_t i = 0;
    int *result = NULL;

    result = tuple_union(tuple1, len1, tuple2, len2, &union_len);
    if (result == NULL) {
        fprintf(stderr, "Failed to compute union\n");
        return EXIT_FAILURE;
    }

    printf("Union: ");
    for (i = 0; i < union_len; i++) {
        printf("%d", result[i]);
        if (i + 1 < union_len) {
            printf(" ");
        }
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}