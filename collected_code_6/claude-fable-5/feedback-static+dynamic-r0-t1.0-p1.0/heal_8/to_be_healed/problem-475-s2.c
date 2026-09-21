#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_KEY_LEN 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    long value;
} CounterEntry;

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t i;

    if (s == NULL) {
        return max_len;
    }

    for (i = 0; i < max_len; i++) {
        if (s[i] == '\0') {
            return i;
        }
    }
    return max_len;
}

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
    return strncmp(ea->key, eb->key, MAX_KEY_LEN);
}

static int sort_counter_by_value(CounterEntry *entries, size_t count)
{
    if (entries == NULL) {
        return -1;
    }
    if (count == 0) {
        return 0;
    }
    if (count > SIZE_MAX / sizeof(CounterEntry)) {
        return -1;
    }
    qsort(entries, count, sizeof(CounterEntry), compare_by_value);
    return 0;
}

static int init_entry(CounterEntry *entry, const char *key, long value)
{
    size_t len;
    int written;

    if (entry == NULL || key == NULL) {
        return -1;
    }

    len = bounded_strlen(key, sizeof(entry->key));
    if (len >= sizeof(entry->key)) {
        return -1;
    }

    memset(entry->key, 0, sizeof(entry->key));
    written = snprintf(entry->key, sizeof(entry->key), "%s", key);
    if (written < 0 || (size_t)written >= sizeof(entry->key)) {
        return -1;
    }
    entry->key[sizeof(entry->key) - 1] = '\0';
    entry->value = value;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     *  Assignment 'count=5', assigned value is 5
     */
    size_t count = 5;
    size_t i;
    CounterEntry *entries;

    /* Possible weaknesses found:
     *  Condition 'count==0' is always false [knownConditionTrueFalse]
     *  Condition 'count==0' is always false
     */
    if (count == 0 || count > SIZE_MAX / sizeof(CounterEntry)) {
        fprintf(stderr, "Allocation size overflow\n");
        return EXIT_FAILURE;
    }

    entries = (CounterEntry *)calloc(count, sizeof(CounterEntry));
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