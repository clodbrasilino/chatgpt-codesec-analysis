#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 32

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_LEN];
    int value;
} Tuple;

static int compare_tuples(const void *a, const void *b)
{
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;

    if (ta->value < tb->value) {
        return -1;
    }
    if (ta->value > tb->value) {
        return 1;
    }
    return 0;
}

static Tuple *find_min_k_records(const Tuple *records, size_t n, size_t k)
{
    Tuple *sorted;
    Tuple *result;

    if (records == NULL || n == 0U || k == 0U || k > n) {
        return NULL;
    }

    sorted = malloc(n * sizeof(*sorted));
    if (sorted == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted, records, n * sizeof(*sorted));
    qsort(sorted, n, sizeof(*sorted), compare_tuples);

    result = malloc(k * sizeof(*result));
    if (result == NULL) {
        free(sorted);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, sorted, k * sizeof(*result));
    free(sorted);

    return result;
}

int main(void)
{
    Tuple records[] = {
        { "Alice", 45 },
        { "Bob", 12 },
        { "Carol", 78 },
        { "Dave", 3 },
        { "Eve", 56 },
        { "Frank", 23 }
    };
    size_t n = sizeof(records) / sizeof(records[0]);
    size_t k = 3U;
    Tuple *min_records;
    size_t i;

    min_records = find_min_k_records(records, n, k);
    if (min_records == NULL) {
        fprintf(stderr, "Failed to find minimum records\n");
        return EXIT_FAILURE;
    }

    printf("Minimum %zu records:\n", k);
    for (i = 0U; i < k; i++) {
        printf("%s: %d\n", min_records[i].name, min_records[i].value);
    }

    free(min_records);

    return EXIT_SUCCESS;
}