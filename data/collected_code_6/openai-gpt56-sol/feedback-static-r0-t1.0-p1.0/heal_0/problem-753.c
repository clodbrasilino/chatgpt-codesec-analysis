#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double value;
} Record;

static int compare_records(const void *lhs, const void *rhs)
{
    const Record *a = lhs;
    const Record *b = rhs;

    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
        return 1;
    }
    if (a->id < b->id) {
        return -1;
    }
    if (a->id > b->id) {
        return 1;
    }
    return 0;
}

static int find_min_k_records(const Record *records, size_t count, size_t k,
                              Record **result)
{
    Record *copy;

    if (result == NULL || (records == NULL && count != 0U) || k > count) {
        return EINVAL;
    }

    *result = NULL;

    if (k == 0U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*copy)) {
        return EOVERFLOW;
    }

    copy = malloc(count * sizeof(*copy));
    if (copy == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0U; i < count; ++i) {
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
    return 0;
}

int main(void)
{
    Record records[] = {
        {1, 8.5},
        {2, 3.2},
        {3, 6.7},
        {4, 1.4},
        {5, 3.2}
    };
    const size_t count = sizeof(records) / sizeof(records[0]);
    const size_t k = 3U;
    Record *minimum_records = NULL;
    int status = find_min_k_records(records, count, k, &minimum_records);

    if (status != 0) {
        fprintf(stderr, "Unable to find records: error %d\n", status);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < k; ++i) {
        if (printf("%d %.2f\n", minimum_records[i].id,
                   minimum_records[i].value) < 0) {
            free(minimum_records);
            return EXIT_FAILURE;
        }
    }

    free(minimum_records);
    return EXIT_SUCCESS;
}