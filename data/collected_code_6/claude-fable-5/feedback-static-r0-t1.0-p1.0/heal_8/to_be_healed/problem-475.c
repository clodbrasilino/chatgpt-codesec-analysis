#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_MAX 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[KEY_MAX];
    int value;
} CounterEntry;

static int set_entry(CounterEntry *entry, const char *key, int value)
{
    size_t key_len;
    int written;

    if (entry == NULL || key == NULL) {
        return -1;
    }

    key_len = strnlen(key, sizeof(entry->key));
    if (key_len >= sizeof(entry->key)) {
        return -1;
    }

    written = snprintf(entry->key, sizeof(entry->key), "%s", key);
    if (written < 0 || (size_t)written >= sizeof(entry->key)) {
        return -1;
    }

    entry->value = value;
    return 0;
}

static int compare_by_value_desc(const void *a, const void *b)
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
    qsort(entries, count, sizeof(CounterEntry), compare_by_value_desc);
    return 0;
}

int main(void)
{
    size_t count = 5;
    size_t i;
    CounterEntry *entries;

    entries = calloc(count, sizeof(CounterEntry));
    if (entries == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (set_entry(&entries[0], "apple", 3) != 0 ||
        set_entry(&entries[1], "banana", 7) != 0 ||
        set_entry(&entries[2], "cherry", 1) != 0 ||
        set_entry(&entries[3], "date", 7) != 0 ||
        set_entry(&entries[4], "elderberry", 5) != 0) {
        fprintf(stderr, "Failed to initialize entries\n");
        free(entries);
        return EXIT_FAILURE;
    }

    if (sort_counter_by_value(entries, count) != 0) {
        fprintf(stderr, "Sorting failed\n");
        free(entries);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        if (printf("%s: %d\n", entries[i].key, entries[i].value) < 0) {
            free(entries);
            return EXIT_FAILURE;
        }
    }

    free(entries);
    return EXIT_SUCCESS;
}