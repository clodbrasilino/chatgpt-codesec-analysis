#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *key;
    size_t key_length;
    const char *value;
    size_t value_length;
} KeyValuePair;

typedef struct ValueNode {
    char *value;
    size_t value_length;
    struct ValueNode *next;
} ValueNode;

typedef struct MapEntry {
    char *key;
    size_t key_length;
    ValueNode *values;
    ValueNode *values_tail;
    struct MapEntry *next;
} MapEntry;

typedef struct {
    MapEntry *head;
    MapEntry *tail;
    size_t size;
} GroupMap;

static char *duplicate_bytes(const char *source, size_t length)
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

static ValueNode *value_node_create(const char *value, size_t value_length)
{
    ValueNode *node;

    if (value == NULL) {
        return NULL;
    }

    node = calloc(1, sizeof(*node));
    if (node == NULL) {
        return NULL;
    }

    node->value = duplicate_bytes(value, value_length);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    node->value_length = value_length;
    return node;
}

static void value_node_destroy(ValueNode *node)
{
    if (node == NULL) {
        return;
    }

    free(node->value);
    free(node);
}

static MapEntry *map_entry_create(const char *key, size_t key_length)
{
    MapEntry *entry;

    if (key == NULL) {
        return NULL;
    }

    entry = calloc(1, sizeof(*entry));
    if (entry == NULL) {
        return NULL;
    }

    entry->key = duplicate_bytes(key, key_length);
    if (entry->key == NULL) {
        free(entry);
        return NULL;
    }

    entry->key_length = key_length;
    return entry;
}

static bool keys_equal(const MapEntry *entry, const char *key, size_t key_length)
{
    if (entry == NULL || key == NULL || entry->key_length != key_length) {
        return false;
    }

    if (key_length == 0) {
        return true;
    }

    return memcmp(entry->key, key, key_length) == 0;
}

static MapEntry *group_map_find(
    GroupMap *map,
    const char *key,
    size_t key_length)
{
    MapEntry *entry;

    if (map == NULL || key == NULL) {
        return NULL;
    }

    for (entry = map->head; entry != NULL; entry = entry->next) {
        if (keys_equal(entry, key, key_length)) {
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
            value_node_destroy(value);
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
        const KeyValuePair *pair = &pairs[index];
        MapEntry *entry;
        ValueNode *value_node;

        if (pair->key == NULL || pair->value == NULL ||
            pair->key_length == SIZE_MAX ||
            pair->value_length == SIZE_MAX) {
            group_map_destroy(map);
            return NULL;
        }

        entry = group_map_find(map, pair->key, pair->key_length);

        value_node = value_node_create(pair->value, pair->value_length);
        if (value_node == NULL) {
            group_map_destroy(map);
            return NULL;
        }

        if (entry == NULL) {
            if (map->size == SIZE_MAX) {
                value_node_destroy(value_node);
                group_map_destroy(map);
                return NULL;
            }

            entry = map_entry_create(pair->key, pair->key_length);
            if (entry == NULL) {
                value_node_destroy(value_node);
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

static bool write_bytes(const char *data, size_t length, FILE *stream)
{
    if (data == NULL || stream == NULL) {
        return false;
    }

    return length == 0 || fwrite(data, 1, length, stream) == length;
}

bool group_map_print(const GroupMap *map)
{
    const MapEntry *entry;

    if (map == NULL) {
        return false;
    }

    for (entry = map->head; entry != NULL; entry = entry->next) {
        const ValueNode *value;
        bool first = true;

        if (!write_bytes(entry->key, entry->key_length, stdout) ||
            fputs(": [", stdout) == EOF) {
            return false;
        }

        for (value = entry->values; value != NULL; value = value->next) {
            if (!first && fputs(", ", stdout) == EOF) {
                return false;
            }

            if (!write_bytes(value->value, value->value_length, stdout)) {
                return false;
            }

            first = false;
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
        {"fruit", sizeof("fruit") - 1, "apple", sizeof("apple") - 1},
        {"color", sizeof("color") - 1, "blue", sizeof("blue") - 1},
        {"fruit", sizeof("fruit") - 1, "banana", sizeof("banana") - 1},
        {"animal", sizeof("animal") - 1, "cat", sizeof("cat") - 1},
        {"color", sizeof("color") - 1, "green", sizeof("green") - 1},
        {"fruit", sizeof("fruit") - 1, "orange", sizeof("orange") - 1}
    };
    GroupMap *map;

    map = group_key_value_pairs(
        pairs,
        sizeof(pairs) / sizeof(pairs[0]));

    if (map == NULL) {
        fputs("Failed to group key-value pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!group_map_print(map)) {
        group_map_destroy(map);
        return EXIT_FAILURE;
    }

    group_map_destroy(map);
    return EXIT_SUCCESS;
}