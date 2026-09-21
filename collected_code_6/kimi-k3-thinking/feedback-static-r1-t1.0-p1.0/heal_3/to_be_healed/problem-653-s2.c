#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    char **values;
    size_t count;
    size_t capacity;
} ValueList;

typedef struct {
    char *key;
    ValueList list;
} MapEntry;

typedef struct {
    MapEntry *entries;
    size_t count;
    size_t capacity;
} Map;

static char *duplicate_string(const char *s)
{
    size_t len;
    size_t size;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strnlen(s, MAX_STRING_LENGTH);
    if (len >= MAX_STRING_LENGTH) {
        return NULL;
    }
    /* Possible weaknesses found:
     *  size is assigned 'len+1' here.
     */
    size = len + 1;
    /* Possible weaknesses found:
     *  Condition 'size<=len' is always false [knownConditionTrueFalse]
     *  Condition 'size<=len' is always false
     */
    if (size <= len || size > MAX_STRING_LENGTH) {
        return NULL;
    }
    copy = (char *)malloc(size);
    if (copy == NULL) {
        return NULL;
    }
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, s, len);
    }
    copy[len] = '\0';
    return copy;
}

static void value_list_init(ValueList *list)
{
    if (list == NULL) {
        return;
    }
    list->values = NULL;
    list->count = 0;
    list->capacity = 0;
}

static void value_list_free(ValueList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        free(list->values[i]);
        list->values[i] = NULL;
    }
    free(list->values);
    list->values = NULL;
    list->count = 0;
    list->capacity = 0;
}

static int value_list_append(ValueList *list, const char *value)
{
    char **new_values;
    char *value_copy;

    if (list == NULL || value == NULL) {
        return -1;
    }

    if (list->count == list->capacity) {
        size_t new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;

        if (new_capacity < list->capacity ||
            new_capacity > SIZE_MAX / sizeof(*new_values)) {
            return -1;
        }
        new_values = (char **)realloc(list->values,
                                      new_capacity * sizeof(*new_values));
        if (new_values == NULL) {
            return -1;
        }
        list->values = new_values;
        list->capacity = new_capacity;
    }

    value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        return -1;
    }

    list->values[list->count] = value_copy;
    list->count++;
    return 0;
}

static void map_init(Map *map)
{
    if (map == NULL) {
        return;
    }
    map->entries = NULL;
    map->count = 0;
    map->capacity = 0;
}

static void map_free(Map *map)
{
    size_t i;

    if (map == NULL) {
        return;
    }
    for (i = 0; i < map->count; i++) {
        free(map->entries[i].key);
        map->entries[i].key = NULL;
        value_list_free(&map->entries[i].list);
    }
    free(map->entries);
    map->entries = NULL;
    map->count = 0;
    map->capacity = 0;
}

static MapEntry *map_find_entry(Map *map, const char *key)
{
    size_t i;

    if (map == NULL || key == NULL) {
        return NULL;
    }
    for (i = 0; i < map->count; i++) {
        if (strcmp(map->entries[i].key, key) == 0) {
            return &map->entries[i];
        }
    }
    return NULL;
}

static int map_add(Map *map, const char *key, const char *value)
{
    MapEntry *entry;
    MapEntry *new_entries;
    ValueList new_list;
    char *key_copy;

    if (map == NULL || key == NULL || value == NULL) {
        return -1;
    }

    entry = map_find_entry(map, key);
    if (entry != NULL) {
        return value_list_append(&entry->list, value);
    }

    if (map->count == map->capacity) {
        size_t new_capacity = (map->capacity == 0) ? 4 : map->capacity * 2;

        if (new_capacity < map->capacity ||
            new_capacity > SIZE_MAX / sizeof(*new_entries)) {
            return -1;
        }
        new_entries = (MapEntry *)realloc(map->entries,
                                          new_capacity * sizeof(*new_entries));
        if (new_entries == NULL) {
            return -1;
        }
        map->entries = new_entries;
        map->capacity = new_capacity;
    }

    key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return -1;
    }

    value_list_init(&new_list);
    if (value_list_append(&new_list, value) != 0) {
        value_list_free(&new_list);
        free(key_copy);
        return -1;
    }

    entry = &map->entries[map->count];
    entry->key = key_copy;
    entry->list = new_list;
    map->count++;
    return 0;
}

int group_pairs(Map *map, const KeyValuePair *pairs, size_t pair_count)
{
    size_t i;

    if (map == NULL) {
        return -1;
    }
    if (pairs == NULL && pair_count > 0) {
        return -1;
    }
    for (i = 0; i < pair_count; i++) {
        if (map_add(map, pairs[i].key, pairs[i].value) != 0) {
            return -1;
        }
    }
    return 0;
}

static void map_print(const Map *map)
{
    size_t i;
    size_t j;

    if (map == NULL) {
        return;
    }
    for (i = 0; i < map->count; i++) {
        printf("%s: [", map->entries[i].key);
        for (j = 0; j < map->entries[i].list.count; j++) {
            printf("%s", map->entries[i].list.values[j]);
            if (j + 1 < map->entries[i].list.count) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    Map map;
    KeyValuePair pairs[] = {
        {"fruit", "apple"},
        {"vegetable", "carrot"},
        {"fruit", "banana"},
        {"vegetable", "broccoli"},
        {"fruit", "cherry"},
        {"grain", "rice"},
        {"grain", "wheat"}
    };
    size_t pair_count;
    int status;

    pair_count = sizeof(pairs) / sizeof(pairs[0]);
    status = EXIT_SUCCESS;

    map_init(&map);

    if (group_pairs(&map, pairs, pair_count) != 0) {
        fprintf(stderr, "Error: failed to group key-value pairs\n");
        status = EXIT_FAILURE;
    } else {
        map_print(&map);
    }

    map_free(&map);
    return status;
}