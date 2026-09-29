#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ValueNode {
    char *value;
    struct ValueNode *next;
} ValueNode;

typedef struct MapEntry {
    char *key;
    ValueNode *values;
    ValueNode *tail;
    struct MapEntry *next;
} MapEntry;

typedef struct {
    MapEntry *head;
} Map;

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(src);
    copy = malloc(len + 1U);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, src, len + 1U);
    return copy;
}

static void free_value_list(ValueNode *node)
{
    while (node != NULL) {
        ValueNode *next = node->next;
        free(node->value);
        free(node);
        node = next;
    }
}

static void map_free(Map *map)
{
    MapEntry *entry;

    if (map == NULL) {
        return;
    }
    entry = map->head;
    while (entry != NULL) {
        MapEntry *next = entry->next;
        free_value_list(entry->values);
        free(entry->key);
        free(entry);
        entry = next;
    }
    map->head = NULL;
}

static MapEntry *map_find(const Map *map, const char *key)
{
    MapEntry *entry;

    if ((map == NULL) || (key == NULL)) {
        return NULL;
    }
    entry = map->head;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

static int map_insert(Map *map, const char *key, const char *value)
{
    MapEntry *entry;
    ValueNode *node;
    char *value_copy;

    if ((map == NULL) || (key == NULL) || (value == NULL)) {
        return -1;
    }

    value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        return -1;
    }

    node = malloc(sizeof(ValueNode));
    if (node == NULL) {
        free(value_copy);
        return -1;
    }
    node->value = value_copy;
    node->next = NULL;

    entry = map_find(map, key);
    if (entry == NULL) {
        char *key_copy = duplicate_string(key);
        if (key_copy == NULL) {
            free(node->value);
            free(node);
            return -1;
        }
        entry = malloc(sizeof(MapEntry));
        if (entry == NULL) {
            free(key_copy);
            free(node->value);
            free(node);
            return -1;
        }
        entry->key = key_copy;
        entry->values = node;
        entry->tail = node;
        entry->next = map->head;
        map->head = entry;
    } else {
        entry->tail->next = node;
        entry->tail = node;
    }
    return 0;
}

static int group_pairs(Map *map, const char *const keys[], const char *const values[], size_t count)
{
    size_t i;

    if ((map == NULL) || (keys == NULL) || (values == NULL)) {
        return -1;
    }
    for (i = 0; i < count; i++) {
        if (map_insert(map, keys[i], values[i]) != 0) {
            return -1;
        }
    }
    return 0;
}

static void map_print(const Map *map)
{
    const MapEntry *entry;

    if (map == NULL) {
        return;
    }
    entry = map->head;
    while (entry != NULL) {
        const ValueNode *node = entry->values;
        printf("%s: [", entry->key);
        while (node != NULL) {
            printf("%s", node->value);
            if (node->next != NULL) {
                printf(", ");
            }
            node = node->next;
        }
        printf("]\n");
        entry = entry->next;
    }
}

int main(void)
{
    Map map = { NULL };
    const char *const keys[] = { "fruit", "vegetable", "fruit", "fruit", "vegetable" };
    const char *const values[] = { "apple", "carrot", "banana", "cherry", "potato" };
    size_t count = sizeof(keys) / sizeof(keys[0]);

    if (group_pairs(&map, keys, values, count) != 0) {
        fprintf(stderr, "Failed to group key-value pairs\n");
        map_free(&map);
        return EXIT_FAILURE;
    }

    map_print(&map);
    map_free(&map);
    return EXIT_SUCCESS;
}