#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NAME_MAX_LEN 32U

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_MAX_LEN];
    int score;
} Record;

static int compare_records(const void *a, const void *b)
{
    const Record *ra = (const Record *)a;
    const Record *rb = (const Record *)b;

    if (ra->score < rb->score) {
        return -1;
    }
    if (ra->score > rb->score) {
        return 1;
    }
    return 0;
}

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i;

    for (i = 0U; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
    }
    return i;
}

static int record_set_name(Record *record, const char *name)
{
    size_t len;

    if (record == NULL || name == NULL) {
        return -1;
    }

    len = bounded_strlen(name, NAME_MAX_LEN);
    if (len >= NAME_MAX_LEN) {
        return -1;
    }

    if (len > sizeof(record->name) - 1U) {
        return -1;
    }

    if (len > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(record->name, name, len);
    }
    record->name[len] = '\0';
    return 0;
}

static Record *find_min_k_records(const Record *records, size_t count, size_t k)
{
    Record *sorted = NULL;
    Record *result = NULL;
    size_t total_size;
    size_t result_size;

    if (records == NULL || count == 0U || k == 0U || k > count) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(Record)) {
        return NULL;
    }

    total_size = count * sizeof(Record);
    result_size = k * sizeof(Record);

    if (result_size > total_size) {
        return NULL;
    }

    sorted = malloc(total_size);
    if (sorted == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted, records, total_size);
    qsort(sorted, count, sizeof(Record), compare_records);

    result = malloc(result_size);
    if (result == NULL) {
        free(sorted);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, sorted, result_size);
    free(sorted);

    return result;
}

int main(void)
{
    static const struct {
        const char *name;
        int score;
    } input[] = {
        {"Alice", 85},
        {"Bob", 42},
        {"Carol", 91},
        {"Dave", 27},
        {"Eve", 63},
        {"Frank", 55}
    };
    size_t count = sizeof(input) / sizeof(input[0]);
    Record records[sizeof(input) / sizeof(input[0])];
    size_t k = 3U;
    size_t i;
    Record *min_records = NULL;

    for (i = 0U; i < count; i++) {
        if (record_set_name(&records[i], input[i].name) != 0) {
            fprintf(stderr, "Invalid record name at index %zu\n", i);
            return EXIT_FAILURE;
        }
        records[i].score = input[i].score;
    }

    min_records = find_min_k_records(records, count, k);
    if (min_records == NULL) {
        fprintf(stderr, "Failed to find minimum records\n");
        return EXIT_FAILURE;
    }

    printf("Minimum %zu records:\n", k);
    for (i = 0U; i < k; i++) {
        printf("%.*s: %d\n", (int)(NAME_MAX_LEN - 1U), min_records[i].name, min_records[i].score);
    }

    free(min_records);
    return EXIT_SUCCESS;
}