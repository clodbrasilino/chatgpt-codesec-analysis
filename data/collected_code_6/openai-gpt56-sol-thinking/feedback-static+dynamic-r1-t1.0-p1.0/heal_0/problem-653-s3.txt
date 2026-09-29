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

typedef struct ValueNode {
    char *value;
    struct ValueNode *next;
} ValueNode;

typedef struct MapEntry {
    char *key;
    ValueNode *values;
    ValueNode *values_tail;
    struct MapEntry *next;
} MapEntry;

typedef struct {
    MapEntry *head;
    MapEntry *tail;
    size_t size;
} GroupMap;

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

static ValueNode *value_node_create(const char *value)
{
    ValueNode *node;

    node = calloc(1, sizeof(*node));
    if (node == NULL) {
        return NULL;
    }

    node->value = duplicate_string(value);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    return node;
}

static MapEntry *map_entry_create(const char *key)
{
    MapEntry *entry;

    entry = calloc(1, sizeof(*entry));
    if (entry == NULL) {
        return NULL;
    }

    entry->key = duplicate_string(key);
    if (entry->key == NULL) {
        free(entry);
        return NULL;
    }

    return entry;
}

static MapEntry *group_map_find(GroupMap *map, const char *key)
{
    MapEntry *entry;

    if (map == NULL || key == NULL) {
        return NULL;
    }

    for (entry = map->head; entry != NULL; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) {
            return entry;
        }
    }

    return NULL;
}

void group_map_destroy(GroupMap *map)
{
    MapEntry *entry;

    if (map == NULL) {
        return;
    }

    entry = map->head;
    while (entry != NULL) {
        MapEntry *next_entry = entry->next;
        ValueNode *value = entry->values;

        while (value != NULL) {
            ValueNode *next_value = value->next;
            free(value->value);
            free(value);
            value = next_value;
        }

        free(entry->key);
        free(entry);
        entry = next_entry;
    }

    free(map);
}

GroupMap *group_key_value_pairs(const KeyValuePair *pairs, size_t count)
{
    GroupMap *map;
    size_t index;

    if ((count != 0 && pairs == NULL) ||
        count > SIZE_MAX / sizeof(*pairs)) {
        return NULL;
    }

    map = calloc(1, sizeof(*map));
    if (map == NULL) {
        return NULL;
    }

    for (index = 0; index < count; ++index) {
        MapEntry *entry;
        ValueNode *value_node;

        if (pairs[index].key == NULL || pairs[index].value == NULL) {
            group_map_destroy(map);
            return NULL;
        }

        entry = group_map_find(map, pairs[index].key);
        value_node = value_node_create(pairs[index].value);
        if (value_node == NULL) {
            group_map_destroy(map);
            return NULL;
        }

        if (entry == NULL) {
            if (map->size == SIZE_MAX) {
                free(value_node->value);
                free(value_node);
                group_map_destroy(map);
                return NULL;
            }

            entry = map_entry_create(pairs[index].key);
            if (entry == NULL) {
                free(value_node->value);
                free(value_node);
                group_map_destroy(map);
                return NULL;
            }

            entry->values = value_node;
            entry->values_tail = value_node;

            if (map->tail == NULL) {
                map->head = entry;
                map->tail = entry;
            } else {
                map->tail->next = entry;
                map->tail = entry;
            }

            ++map->size;
        } else {
            entry->values_tail->next = value_node;
            entry->values_tail = value_node;
        }
    }

    return map;
}

bool group_map_print(const GroupMap *map)
{
    const MapEntry *entry;

    if (map == NULL) {
        return false;
    }

    for (entry = map->head; entry != NULL; entry = entry->next) {
        const ValueNode *value;

        if (printf("%s: [", entry->key) < 0) {
            return false;
        }

        for (value = entry->values; value != NULL; value = value->next) {
            if (value != entry->values && fputs(", ", stdout) == EOF) {
                return false;
            }

            if (fputs(value->value, stdout) == EOF) {
                return false;
            }
        }

        if (fputs("]\n", stdout) == EOF) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    static const KeyValuePair pairs[] = {
        {"fruit", "apple"},
        {"color", "blue"},
        {"fruit", "banana"},
        {"animal", "cat"},
        {"color", "green"},
        {"fruit", "orange"}
    };
    GroupMap *map;

    map = group_key_value_pairs(pairs, sizeof(pairs) / sizeof(pairs[0]));
    if (map == NULL) {
        if (fputs("Failed to group key-value pairs.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!group_map_print(map)) {
        group_map_destroy(map);
        return EXIT_FAILURE;
    }

    group_map_destroy(map);
    return EXIT_SUCCESS;
}