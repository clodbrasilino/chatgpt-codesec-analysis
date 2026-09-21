#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_KEY_LEN 64

typedef struct {
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

static CounterEntry *allocate_entries(size_t count)
{
    if (count == 0 || count > SIZE_MAX / sizeof(CounterEntry)) {
        return NULL;
    }
    return (CounterEntry *)calloc(count, sizeof(CounterEntry));
}

static int populate_entries(CounterEntry *entries, size_t count)
{
    static const struct {
        const char *key;
        long value;
    } data[] = {
        { "apple", 3L },
        { "banana", 7L },
        { "cherry", 1L },
        { "date", 7L },
        { "elderberry", 5L }
    };
    size_t data_count = sizeof(data) / sizeof(data[0]);
    size_t i;

    if (entries == NULL || count < data_count) {
        return -1;
    }

    for (i = 0; i < data_count; i++) {
        if (init_entry(&entries[i], data[i].key, data[i].value) != 0) {
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    const size_t count = 5;
    size_t i;
    CounterEntry *entries;

    entries = allocate_entries(count);
    if (entries == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (populate_entries(entries, count) != 0) {
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