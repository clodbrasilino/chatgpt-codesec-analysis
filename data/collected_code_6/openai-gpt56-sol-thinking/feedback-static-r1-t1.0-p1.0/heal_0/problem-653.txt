#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    const char *value;
} KeyValuePair;

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} ValueList;

typedef struct {
    char *key;
    ValueList values;
} MapEntry;

typedef struct {
    MapEntry *entries;
    size_t count;
    size_t capacity;
} GroupedMap;

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1);
    return copy;
}

static bool reserve_values(ValueList *list, size_t required)
{
    size_t new_capacity;
    char **new_items;

    if (required <= list->capacity) {
        return true;
    }

    new_capacity = list->capacity == 0 ? 4 : list->capacity;
    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*new_items)) {
        return false;
    }

    new_items = realloc(list->items, new_capacity * sizeof(*new_items));
    if (new_items == NULL) {
        return false;
    }

    list->items = new_items;
    list->capacity = new_capacity;
    return true;
}

static bool append_value(ValueList *list, const char *value)
{
    char *copy;

    if (list == NULL || value == NULL || list->count == SIZE_MAX) {
        return false;
    }

    if (!reserve_values(list, list->count + 1)) {
        return false;
    }

    copy = duplicate_string(value);
    if (copy == NULL) {
        return false;
    }

    list->items[list->count] = copy;
    list->count++;
    return true;
}

static void destroy_value_list(ValueList *list)
{
    size_t index;

    if (list == NULL) {
        return;
    }

    for (index = 0; index < list->count; index++) {
        free(list->items[index]);
    }

    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

static bool reserve_entries(GroupedMap *map, size_t required)
{
    size_t new_capacity;
    MapEntry *new_entries;

    if (required <= map->capacity) {
        return true;
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
        return false;
    }

    new_entries = realloc(map->entries, new_capacity * sizeof(*new_entries));
    if (new_entries == NULL) {
        return false;
    }

    map->entries = new_entries;
    map->capacity = new_capacity;
    return true;
}

static size_t find_entry(const GroupedMap *map, const char *key)
{
    size_t index;

    for (index = 0; index < map->count; index++) {
        if (strcmp(map->entries[index].key, key) == 0) {
            return index;
        }
    }

    return SIZE_MAX;
}

void free_grouped_map(GroupedMap *map)
{
    size_t index;

    if (map == NULL) {
        return;
    }

    for (index = 0; index < map->count; index++) {
        free(map->entries[index].key);
        destroy_value_list(&map->entries[index].values);
    }

    free(map->entries);
    free(map);
}

GroupedMap *group_key_value_pairs(const KeyValuePair *pairs, size_t pair_count)
{
    GroupedMap *map;
    size_t pair_index;

    if (pairs == NULL && pair_count != 0) {
        return NULL;
    }

    map = calloc(1, sizeof(*map));
    if (map == NULL) {
        return NULL;
    }

    for (pair_index = 0; pair_index < pair_count; pair_index++) {
        size_t entry_index;

        if (pairs[pair_index].key == NULL || pairs[pair_index].value == NULL) {
            free_grouped_map(map);
            return NULL;
        }

        entry_index = find_entry(map, pairs[pair_index].key);
        if (entry_index != SIZE_MAX) {
            if (!append_value(&map->entries[entry_index].values,
                              pairs[pair_index].value)) {
                free_grouped_map(map);
                return NULL;
            }
            continue;
        }

        if (map->count == SIZE_MAX ||
            !reserve_entries(map, map->count + 1)) {
            free_grouped_map(map);
            return NULL;
        }

        map->entries[map->count].key =
            duplicate_string(pairs[pair_index].key);
        map->entries[map->count].values.items = NULL;
        map->entries[map->count].values.count = 0;
        map->entries[map->count].values.capacity = 0;

        if (map->entries[map->count].key == NULL ||
            !append_value(&map->entries[map->count].values,
                          pairs[pair_index].value)) {
            free(map->entries[map->count].key);
            destroy_value_list(&map->entries[map->count].values);
            free_grouped_map(map);
            return NULL;
        }

        map->count++;
    }

    return map;
}

static bool print_grouped_map(const GroupedMap *map)
{
    size_t entry_index;

    if (map == NULL) {
        return false;
    }

    for (entry_index = 0; entry_index < map->count; entry_index++) {
        size_t value_index;

        if (printf("%s:", map->entries[entry_index].key) < 0) {
            return false;
        }

        for (value_index = 0;
             value_index < map->entries[entry_index].values.count;
             value_index++) {
            if (printf(" %s",
                       map->entries[entry_index].values.items[value_index]) < 0) {
                return false;
            }
        }

        if (putchar('\n') == EOF) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const KeyValuePair pairs[] = {
        {"fruit", "apple"},
        {"color", "red"},
        {"fruit", "banana"},
        {"color", "blue"},
        {"fruit", "orange"},
        {"animal", "cat"}
    };
    GroupedMap *map;
    int status;

    map = group_key_value_pairs(pairs, sizeof(pairs) / sizeof(pairs[0]));
    if (map == NULL) {
        if (fputs("Failed to group key-value pairs\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    status = print_grouped_map(map) ? EXIT_SUCCESS : EXIT_FAILURE;
    free_grouped_map(map);
    return status;
}