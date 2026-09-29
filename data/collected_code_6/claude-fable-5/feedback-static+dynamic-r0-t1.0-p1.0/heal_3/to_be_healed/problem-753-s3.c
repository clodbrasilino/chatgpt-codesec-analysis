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

static int set_record(Record *record, const char *name, int score)
{
    size_t name_len;

    if (record == NULL || name == NULL) {
        return -1;
    }

    name_len = strnlen(name, NAME_MAX_LEN);
    if (name_len >= NAME_MAX_LEN) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(record->name, name, name_len);
    record->name[name_len] = '\0';
    record->score = score;

    return 0;
}

static Record *find_min_k_records(const Record *records, size_t count, size_t k)
{
    Record *sorted = NULL;
    Record *result = NULL;

    if (records == NULL || count == 0U || k == 0U || k > count) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(Record)) {
        return NULL;
    }

    sorted = malloc(count * sizeof(Record));
    if (sorted == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted, records, count * sizeof(Record));
    qsort(sorted, count, sizeof(Record), compare_records);

    result = malloc(k * sizeof(Record));
    if (result == NULL) {
        free(sorted);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, sorted, k * sizeof(Record));
    free(sorted);

    return result;
}

int main(void)
{
    Record records[6];
    size_t count = sizeof(records) / sizeof(records[0]);
    size_t k = 3U;
    size_t i;
    Record *min_records = NULL;

    if (set_record(&records[0], "Alice", 85) != 0 ||
        set_record(&records[1], "Bob", 42) != 0 ||
        set_record(&records[2], "Carol", 91) != 0 ||
        set_record(&records[3], "Dave", 27) != 0 ||
        set_record(&records[4], "Eve", 63) != 0 ||
        set_record(&records[5], "Frank", 55) != 0) {
        fprintf(stderr, "Failed to initialize records\n");
        return EXIT_FAILURE;
    }

    min_records = find_min_k_records(records, count, k);
    if (min_records == NULL) {
        fprintf(stderr, "Failed to find minimum records\n");
        return EXIT_FAILURE;
    }

    printf("Minimum %zu records:\n", k);
    for (i = 0U; i < k; i++) {
        printf("%s: %d\n", min_records[i].name, min_records[i].score);
    }

    free(min_records);
    return EXIT_SUCCESS;
}