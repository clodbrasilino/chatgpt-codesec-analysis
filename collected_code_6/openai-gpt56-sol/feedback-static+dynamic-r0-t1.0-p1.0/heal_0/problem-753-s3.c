#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Record;

static int compare_records(const void *lhs, const void *rhs)
{
    const Record *a = lhs;
    const Record *b = rhs;

    if (a->key < b->key) {
        return -1;
    }
    if (a->key > b->key) {
        return 1;
    }
    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
        return 1;
    }
    return 0;
}

static int find_min_k_records(const Record *records, size_t count, size_t k,
                              Record **result, size_t *result_count)
{
    Record *copy;

    if (result == NULL || result_count == NULL) {
        return EINVAL;
    }

    *result = NULL;
    *result_count = 0;

    if ((records == NULL && count != 0) || k > count) {
        return EINVAL;
    }

    if (k == 0) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*copy)) {
        return EOVERFLOW;
    }

    copy = malloc(count * sizeof(*copy));
    if (copy == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0; i < count; ++i) {
        copy[i] = records[i];
    }

    qsort(copy, count, sizeof(*copy), compare_records);

    if (k < count) {
        Record *smaller = realloc(copy, k * sizeof(*copy));
        if (smaller != NULL) {
            copy = smaller;
        }
    }

    *result = copy;
    *result_count = k;
    return 0;
}

int main(void)
{
    Record records[] = {
        {7, 70},
        {2, 20},
        {5, 50},
        {1, 10},
        {3, 30},
        {2, 15}
    };
    const size_t count = sizeof(records) / sizeof(records[0]);
    const size_t k = 3;
    Record *minimum_records = NULL;
    size_t minimum_count = 0;
    int status;

    status = find_min_k_records(records, count, k, &minimum_records,
                                &minimum_count);
    if (status != 0) {
        fprintf(stderr, "find_min_k_records failed: %d\n", status);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < minimum_count; ++i) {
        if (printf("(%d, %d)\n", minimum_records[i].key,
                   minimum_records[i].value) < 0) {
            free(minimum_records);
            return EXIT_FAILURE;
        }
    }

    free(minimum_records);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}