#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *key;
    size_t key_length;
    const char *value;
    size_t value_length;
} KeyValuePair;

typedef struct {
    char *data;
    size_t length;
} MapValue;

typedef struct {
    char *key;
    size_t key_length;
    MapValue *values;
    size_t value_count;
    size_t value_capacity;
} MapEntry;

typedef struct {
    MapEntry *entries;
    size_t count;
    size_t capacity;
} MapOfLists;

static char *copy_bytes(const char *source, size_t length)
{
    char *copy;
    size_t index;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    for (index = 0; index < length; ++index) {
        copy[index] = source[index];
    }

    copy[length] = '\0';
    return copy;
}

static int bytes_equal(const char *left, const char *right, size_t length)
{
    size_t index;

    for (index = 0; index < length; ++index) {
        if (left[index] != right[index]) {
            return 0;
        }
    }

    return 1;
}

static int reserve_entries(MapOfLists *map, size_t required)
{
    size_t new_capacity;
    MapEntry *new_entries;

    if (map == NULL) {
        return 0;
    }

    if (required <= map->capacity) {
        return 1;
    }

    new_capacity = map->capacity == 0 ? 4 : map->capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_entries)) {
        return 0;
    }

    new_entries = realloc(
        map->entries,
        new_capacity * sizeof(*new_entries)
    );

    if (new_entries == NULL) {
        return 0;
    }

    map->entries = new_entries;
    map->capacity = new_capacity;
    return 1;
}

static int reserve_values(MapEntry *entry, size_t required)
{
    size_t new_capacity;
    MapValue *new_values;

    if (entry == NULL) {
        return 0;
    }

    if (required <= entry->value_capacity) {
        return 1;
    }

    new_capacity = entry->value_capacity == 0 ? 4 : entry->value_capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_values)) {
        return 0;
    }

    new_values = realloc(
        entry->values,
        new_capacity * sizeof(*new_values)
    );

    if (new_values == NULL) {
        return 0;
    }

    entry->values = new_values;
    entry->value_capacity = new_capacity;
    return 1;
}

static MapEntry *find_entry(
    MapOfLists *map,
    const char *key,
    size_t key_length
)
{
    size_t index;

    if (map == NULL || key == NULL) {
        return NULL;
    }

    for (index = 0; index < map->count; ++index) {
        MapEntry *entry = &map->entries[index];

        if (entry->key_length == key_length &&
            bytes_equal(entry->key, key, key_length)) {
            return entry;
        }
    }

    return NULL;
}

static int append_value(
    MapEntry *entry,
    const char *value,
    size_t value_length
)
{
    char *value_copy;

    if (entry == NULL || value == NULL ||
        entry->value_count == SIZE_MAX) {
        return 0;
    }

    value_copy = copy_bytes(value, value_length);
    if (value_copy == NULL) {
        return 0;
    }

    if (!reserve_values(entry, entry->value_count + 1)) {
        free(value_copy);
        return 0;
    }

    entry->values[entry->value_count].data = value_copy;
    entry->values[entry->value_count].length = value_length;
    ++entry->value_count;
    return 1;
}

static void free_entry(MapEntry *entry)
{
    size_t value_index;

    if (entry == NULL) {
        return;
    }

    free(entry->key);

    for (value_index = 0;
         value_index < entry->value_count;
         ++value_index) {
        free(entry->values[value_index].data);
    }

    free(entry->values);

    entry->key = NULL;
    entry->key_length = 0;
    entry->values = NULL;
    entry->value_count = 0;
    entry->value_capacity = 0;
}

void map_of_lists_free(MapOfLists *map)
{
    size_t entry_index;

    if (map == NULL) {
        return;
    }

    for (entry_index = 0;
         entry_index < map->count;
         ++entry_index) {
        free_entry(&map->entries[entry_index]);
    }

    free(map->entries);
    free(map);
}

MapOfLists *group_key_value_pairs(
    const KeyValuePair *pairs,
    size_t pair_count
)
{
    MapOfLists *map;
    size_t index;

    if (pair_count > 0 && pairs == NULL) {
        return NULL;
    }

    map = calloc(1, sizeof(*map));
    if (map == NULL) {
        return NULL;
    }

    for (index = 0; index < pair_count; ++index) {
        const KeyValuePair *pair = &pairs[index];
        MapEntry *entry;

        if (pair->key == NULL || pair->value == NULL) {
            map_of_lists_free(map);
            return NULL;
        }

        entry = find_entry(map, pair->key, pair->key_length);

        if (entry != NULL) {
            if (!append_value(
                    entry,
                    pair->value,
                    pair->value_length)) {
                map_of_lists_free(map);
                return NULL;
            }

            continue;
        }

        if (map->count == SIZE_MAX ||
            !reserve_entries(map, map->count + 1)) {
            map_of_lists_free(map);
            return NULL;
        }

        entry = &map->entries[map->count];
        entry->key = NULL;
        entry->key_length = 0;
        entry->values = NULL;
        entry->value_count = 0;
        entry->value_capacity = 0;

        entry->key = copy_bytes(pair->key, pair->key_length);
        if (entry->key == NULL) {
            map_of_lists_free(map);
            return NULL;
        }

        entry->key_length = pair->key_length;

        if (!append_value(
                entry,
                pair->value,
                pair->value_length)) {
            free_entry(entry);
            map_of_lists_free(map);
            return NULL;
        }

        ++map->count;
    }

    return map;
}

static int write_bytes(const char *data, size_t length)
{
    if (data == NULL) {
        return 0;
    }

    if (length == 0) {
        return 1;
    }

    return fwrite(data, 1, length, stdout) == length;
}

static int print_map(const MapOfLists *map)
{
    size_t entry_index;
    size_t value_index;

    if (map == NULL) {
        return 0;
    }

    for (entry_index = 0;
         entry_index < map->count;
         ++entry_index) {
        const MapEntry *entry = &map->entries[entry_index];

        if (!write_bytes(entry->key, entry->key_length) ||
            fputs(": [", stdout) == EOF) {
            return 0;
        }

        for (value_index = 0;
             value_index < entry->value_count;
             ++value_index) {
            const MapValue *value = &entry->values[value_index];

            if (value_index > 0 &&
                fputs(", ", stdout) == EOF) {
                return 0;
            }

            if (fputc('"', stdout) == EOF ||
                !write_bytes(value->data, value->length) ||
                fputc('"', stdout) == EOF) {
                return 0;
            }
        }

        if (fputs("]\n", stdout) == EOF) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    const KeyValuePair pairs[] = {
        {"fruit", sizeof("fruit") - 1, "apple", sizeof("apple") - 1},
        {"color", sizeof("color") - 1, "red", sizeof("red") - 1},
        {"fruit", sizeof("fruit") - 1, "banana", sizeof("banana") - 1},
        {"color", sizeof("color") - 1, "blue", sizeof("blue") - 1},
        {"fruit", sizeof("fruit") - 1, "orange", sizeof("orange") - 1},
        {"size", sizeof("size") - 1, "large", sizeof("large") - 1}
    };
    const size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);
    MapOfLists *map;
    int status = EXIT_SUCCESS;

    map = group_key_value_pairs(pairs, pair_count);
    if (map == NULL) {
        fputs("Failed to group key-value pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_map(map) || fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    map_of_lists_free(map);
    return status;
}