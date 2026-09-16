#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[64];
    int value;
} CounterEntry;

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

    strncpy(entries[0].key, "apple", sizeof(entries[0].key) - 1);
    entries[0].value = 3;
    strncpy(entries[1].key, "banana", sizeof(entries[1].key) - 1);
    entries[1].value = 7;
    strncpy(entries[2].key, "cherry", sizeof(entries[2].key) - 1);
    entries[2].value = 1;
    strncpy(entries[3].key, "date", sizeof(entries[3].key) - 1);
    entries[3].value = 7;
    strncpy(entries[4].key, "elderberry", sizeof(entries[4].key) - 1);
    entries[4].value = 5;

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