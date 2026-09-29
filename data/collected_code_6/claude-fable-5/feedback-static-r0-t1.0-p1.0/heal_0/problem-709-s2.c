#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Pair;

typedef struct {
    int value;
    int *keys;
    size_t key_count;
    size_t key_capacity;
} ValueEntry;

static void free_entries(ValueEntry *entries, size_t count)
{
    size_t i;

    if (entries == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(entries[i].keys);
    }
    free(entries);
}

static int value_entry_add_key(ValueEntry *entry, int key)
{
    size_t i;

    for (i = 0; i < entry->key_count; i++) {
        if (entry->keys[i] == key) {
            return 0;
        }
    }
    if (entry->key_count == entry->key_capacity) {
        size_t new_capacity = (entry->key_capacity == 0) ? 4U : entry->key_capacity * 2U;
        int *tmp = realloc(entry->keys, new_capacity * sizeof(int));
        if (tmp == NULL) {
            return -1;
        }
        entry->keys = tmp;
        entry->key_capacity = new_capacity;
    }
    entry->keys[entry->key_count] = key;
    entry->key_count++;
    return 0;
}

static int count_unique_keys(const Pair *pairs, size_t pair_count,
                             ValueEntry **out_entries, size_t *out_count)
{
    ValueEntry *entries = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t i;
    size_t j;

    if (pairs == NULL || out_entries == NULL || out_count == NULL) {
        return -1;
    }

    for (i = 0; i < pair_count; i++) {
        ValueEntry *entry = NULL;

        for (j = 0; j < count; j++) {
            if (entries[j].value == pairs[i].value) {
                entry = &entries[j];
                break;
            }
        }

        if (entry == NULL) {
            if (count == capacity) {
                size_t new_capacity = (capacity == 0) ? 4U : capacity * 2U;
                ValueEntry *tmp = realloc(entries, new_capacity * sizeof(ValueEntry));
                if (tmp == NULL) {
                    free_entries(entries, count);
                    return -1;
                }
                entries = tmp;
                capacity = new_capacity;
            }
            entries[count].value = pairs[i].value;
            entries[count].keys = NULL;
            entries[count].key_count = 0;
            entries[count].key_capacity = 0;
            entry = &entries[count];
            count++;
        }

        if (value_entry_add_key(entry, pairs[i].key) != 0) {
            free_entries(entries, count);
            return -1;
        }
    }

    *out_entries = entries;
    *out_count = count;
    return 0;
}

int main(void)
{
    Pair pairs[] = {
        {1, 3}, {2, 3}, {1, 3}, {3, 5},
        {4, 5}, {3, 5}, {5, 7}, {5, 7}
    };
    size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);
    ValueEntry *entries = NULL;
    size_t entry_count = 0;
    size_t i;

    if (count_unique_keys(pairs, pair_count, &entries, &entry_count) != 0) {
        if (fprintf(stderr, "Failed to count unique keys\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < entry_count; i++) {
        if (printf("Value %d has %zu unique key(s)\n",
                   entries[i].value, entries[i].key_count) < 0) {
            free_entries(entries, entry_count);
            return EXIT_FAILURE;
        }
    }

    free_entries(entries, entry_count);
    return EXIT_SUCCESS;
}