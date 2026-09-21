#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} StringView;

typedef struct {
    StringView key;
    StringView value;
} KeyValuePair;

typedef struct {
    char *data;
    size_t length;
} OwnedString;

typedef struct {
    OwnedString *items;
    size_t count;
    size_t capacity;
} ValueList;

typedef struct {
    OwnedString key;
    ValueList values;
} MapEntry;

typedef struct {
    MapEntry *entries;
    size_t count;
    size_t capacity;
} GroupedMap;

static bool duplicate_string(const char *source, size_t length,
                             OwnedString *destination)
{
    char *copy;
    size_t index;

    if (source == NULL || destination == NULL || length == SIZE_MAX) {
        return false;
    }

    destination->data = NULL;
    destination->length = 0;

    copy = malloc(length + 1);
    if (copy == NULL) {
        return false;
    }

    for (index = 0; index < length; index++) {
        copy[index] = source[index];
    }

    copy[length] = '\0';
    destination->data = copy;
    destination->length = length;
    return true;
}

static bool reserve_values(ValueList *list, size_t required)
{
    size_t new_capacity;
    OwnedString *new_items;

    if (list == NULL) {
        return false;
    }

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

    new_items = realloc(list->items,
                        new_capacity * sizeof(*new_items));
    if (new_items == NULL) {
        return false;
    }

    list->items = new_items;
    list->capacity = new_capacity;
    return true;
}

static bool append_value(ValueList *list, StringView value)
{
    OwnedString copy;

    if (list == NULL || value.data == NULL ||
        list->count == SIZE_MAX) {
        return false;
    }

    if (!reserve_values(list, list->count + 1)) {
        return false;
    }

    if (!duplicate_string(value.data, value.length, &copy)) {
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
        free(list->items[index].data);
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

    if (map == NULL) {
        return false;
    }

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

    new_entries = realloc(map->entries,
                          new_capacity * sizeof(*new_entries));
    if (new_entries == NULL) {
        return false;
    }

    map->entries = new_entries;
    map->capacity = new_capacity;
    return true;
}

static bool strings_equal(const OwnedString *left, StringView right)
{
    if (left == NULL || left->data == NULL || right.data == NULL) {
        return false;
    }

    if (left->length != right.length) {
        return false;
    }

    if (left->length == 0) {
        return true;
    }

    return memcmp(left->data, right.data, left->length) == 0;
}

static size_t find_entry(const GroupedMap *map, StringView key)
{
    size_t index;

    if (map == NULL || key.data == NULL) {
        return SIZE_MAX;
    }

    for (index = 0; index < map->count; index++) {
        if (strings_equal(&map->entries[index].key, key)) {
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
        free(map->entries[index].key.data);
        destroy_value_list(&map->entries[index].values);
    }

    free(map->entries);
    free(map);
}

GroupedMap *group_key_value_pairs(const KeyValuePair *pairs,
                                  size_t pair_count)
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
        MapEntry *entry;

        if (pairs[pair_index].key.data == NULL ||
            pairs[pair_index].value.data == NULL) {
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

        entry = &map->entries[map->count];
        entry->key.data = NULL;
        entry->key.length = 0;
        entry->values.items = NULL;
        entry->values.count = 0;
        entry->values.capacity = 0;

        if (!duplicate_string(pairs[pair_index].key.data,
                              pairs[pair_index].key.length,
                              &entry->key) ||
            !append_value(&entry->values,
                          pairs[pair_index].value)) {
            free(entry->key.data);
            destroy_value_list(&entry->values);
            free_grouped_map(map);
            return NULL;
        }

        map->count++;
    }

    return map;
}

static bool write_string(const OwnedString *string)
{
    if (string == NULL || string->data == NULL) {
        return false;
    }

    if (string->length == 0) {
        return true;
    }

    return fwrite(string->data, 1, string->length, stdout) ==
           string->length;
}

static bool print_grouped_map(const GroupedMap *map)
{
    size_t entry_index;

    if (map == NULL) {
        return false;
    }

    for (entry_index = 0; entry_index < map->count; entry_index++) {
        size_t value_index;
        const MapEntry *entry = &map->entries[entry_index];

        if (!write_string(&entry->key) || fputc(':', stdout) == EOF) {
            return false;
        }

        for (value_index = 0;
             value_index < entry->values.count;
             value_index++) {
            if (fputc(' ', stdout) == EOF ||
                !write_string(&entry->values.items[value_index])) {
                return false;
            }
        }

        if (fputc('\n', stdout) == EOF) {
            return false;
        }
    }

    return true;
}

#define STRING_VIEW_LITERAL(value) \
    { (value), sizeof(value) - 1 }

#define KEY_VALUE_PAIR_LITERAL(key_value, mapped_value) \
    { STRING_VIEW_LITERAL(key_value), STRING_VIEW_LITERAL(mapped_value) }

int main(void)
{
    const KeyValuePair pairs[] = {
        KEY_VALUE_PAIR_LITERAL("fruit", "apple"),
        KEY_VALUE_PAIR_LITERAL("color", "red"),
        KEY_VALUE_PAIR_LITERAL("fruit", "banana"),
        KEY_VALUE_PAIR_LITERAL("color", "blue"),
        KEY_VALUE_PAIR_LITERAL("fruit", "orange"),
        KEY_VALUE_PAIR_LITERAL("animal", "cat")
    };
    GroupedMap *map;
    int status;

    map = group_key_value_pairs(
        pairs, sizeof(pairs) / sizeof(pairs[0]));

    if (map == NULL) {
        fputs("Failed to group key-value pairs\n", stderr);
        return EXIT_FAILURE;
    }

    status = print_grouped_map(map) ? EXIT_SUCCESS : EXIT_FAILURE;
    free_grouped_map(map);
    return status;
}