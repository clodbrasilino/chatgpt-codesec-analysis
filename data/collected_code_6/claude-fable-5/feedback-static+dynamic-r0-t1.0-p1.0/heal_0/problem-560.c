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
    size_t total;
    size_t i;
    size_t count;
    int *combined;
    int *result;

    if (first == NULL || second == NULL || result_len == NULL) {
        return NULL;
    }

    if (first_len > SIZE_MAX - second_len) {
        return NULL;
    }

    total = first_len + second_len;
    if (total == 0) {
        *result_len = 0;
        return NULL;
    }

    if (total > SIZE_MAX / sizeof(int)) {
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
            combined[count] = combined[i];
            count++;
        }
    }

    result = realloc(combined, count * sizeof(int));
    if (result == NULL) {
        result = combined;
    }

    *result_len = count;
    return result;
}

int main(void)
{
    int tuple_a[] = {3, 4, 5, 6};
    int tuple_b[] = {5, 7, 4, 10};
    size_t len_a = sizeof(tuple_a) / sizeof(tuple_a[0]);
    size_t len_b = sizeof(tuple_b) / sizeof(tuple_b[0]);
    size_t union_len = 0;
    size_t i;
    int *result;

    result = tuple_union(tuple_a, len_a, tuple_b, len_b, &union_len);
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