#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NAME_MAX_LEN 64U

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_MAX_LEN];
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

static int set_tuple_name(Tuple *t, const char *name)
{
    size_t len;

    if (t == NULL || name == NULL) {
        return -1;
    }

    len = strnlen(name, NAME_MAX_LEN);
    if (len >= NAME_MAX_LEN) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(t->name, name, len);
    t->name[len] = '\0';
    return 0;
}

static Tuple *find_min_k_records(const Tuple *records, size_t n, size_t k)
{
    Tuple *sorted = NULL;
    Tuple *result = NULL;

    if (records == NULL || n == 0U || k == 0U || k > n) {
        return NULL;
    }

    if (n > SIZE_MAX / sizeof(Tuple)) {
        return NULL;
    }

    sorted = malloc(n * sizeof(Tuple));
    if (sorted == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted, records, n * sizeof(Tuple));
    qsort(sorted, n, sizeof(Tuple), compare_tuples);

    result = malloc(k * sizeof(Tuple));
    if (result == NULL) {
        free(sorted);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, sorted, k * sizeof(Tuple));
    free(sorted);

    return result;
}

int main(void)
{
    Tuple records[5];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *names[5] = {"Manjeet", "Akshat", "Akash", "Nikhil", "Rohit"};
    const int values[5] = {10, 4, 2, 8, 6};
    size_t n = 5U;
    size_t k = 2U;
    Tuple *min_records = NULL;
    size_t i;

    memset(records, 0, sizeof(records));

    for (i = 0U; i < n; i++) {
        if (set_tuple_name(&records[i], names[i]) != 0) {
            if (fprintf(stderr, "Failed to initialize record\n") < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
        records[i].value = values[i];
    }

    min_records = find_min_k_records(records, n, k);
    if (min_records == NULL) {
        if (fprintf(stderr, "Failed to find minimum records\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Minimum %zu records:\n", k) < 0) {
        free(min_records);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < k; i++) {
        if (printf("(%s, %d)\n", min_records[i].name, min_records[i].value) < 0) {
            free(min_records);
            return EXIT_FAILURE;
        }
    }

    free(min_records);
    return EXIT_SUCCESS;
}