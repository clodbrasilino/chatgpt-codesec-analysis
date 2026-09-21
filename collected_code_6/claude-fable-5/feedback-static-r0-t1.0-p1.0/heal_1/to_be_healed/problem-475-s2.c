#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    long value;
} CounterEntry;

static int compare_by_value(const void *a, const void *b)
{
    const CounterEntry *ea = (const CounterEntry *)a;
    const CounterEntry *eb = (const CounterEntry *)b;

    if (ea->value < eb->value) {
        return 1;
    }
    if (ea->value > eb->value) {
        return -1;
    }
    return strcmp(ea->key, eb->key);
}

static int sort_counter_by_value(CounterEntry *entries, size_t count)
{
    if (entries == NULL) {
        return -1;
    }
    if (count == 0) {
        return 0;
    }
    qsort(entries, count, sizeof(CounterEntry), compare_by_value);
    return 0;
}

static int init_entry(CounterEntry *entry, const char *key, long value)
{
    size_t len;

    if (entry == NULL || key == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(key);
    if (len >= MAX_KEY_LEN) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(entry->key, key, len + 1U);
    entry->value = value;
    return 0;
}

int main(void)
{
    size_t count = 5;
    size_t i;
    CounterEntry *entries;

    entries = (CounterEntry *)malloc(count * sizeof(CounterEntry));
    if (entries == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (init_entry(&entries[0], "apple", 3L) != 0 ||
        init_entry(&entries[1], "banana", 7L) != 0 ||
        init_entry(&entries[2], "cherry", 1L) != 0 ||
        init_entry(&entries[3], "date", 7L) != 0 ||
        init_entry(&entries[4], "elderberry", 5L) != 0) {
        fprintf(stderr, "Entry initialization failed\n");
        free(entries);
        return EXIT_FAILURE;
    }

    if (sort_counter_by_value(entries, count) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free(entries);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s: %ld\n", entries[i].key, entries[i].value) < 0) {
            free(entries);
            return EXIT_FAILURE;
        }
    }

    free(entries);
    entries = NULL;
    return EXIT_SUCCESS;
}