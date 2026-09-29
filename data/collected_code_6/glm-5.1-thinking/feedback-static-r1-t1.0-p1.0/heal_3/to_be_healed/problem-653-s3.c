#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct ValueNode {
    char *value;
    struct ValueNode *next;
} ValueNode;

typedef struct MapEntry {
    char *key;
    ValueNode *values;
    struct MapEntry *next;
} MapEntry;

typedef struct Map {
    MapEntry *head;
} Map;

static char *my_strdup(const char *s) {
    if (!s) return NULL;
    size_t len = strnlen(s, SIZE_MAX);
    if (len == SIZE_MAX) return NULL;
    len++;
    char *d = malloc(len);
    if (d) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(d, s, len);
    }
    return d;
}

static void free_map(Map *map) {
    if (!map) return;
    MapEntry *entry = map->head;
    while (entry) {
        MapEntry *next_entry = entry->next;
        free(entry->key);
        ValueNode *vnode = entry->values;
        while (vnode) {
            ValueNode *next_vnode = vnode->next;
            free(vnode->value);
            free(vnode);
            vnode = next_vnode;
        }
        free(entry);
        entry = next_entry;
    }
    free(map);
}

Map *group_pairs(const char *keys[], const char *values[], size_t count) {
    if (!keys || !values) return NULL;

    Map *map = malloc(sizeof(Map));
    if (!map) return NULL;
    map->head = NULL;

    for (size_t i = 0; i < count; i++) {
        if (!keys[i] || !values[i]) {
            free_map(map);
            return NULL;
        }

        MapEntry *entry = NULL;
        MapEntry *curr = map->head;
        while (curr) {
            if (strcmp(curr->key, keys[i]) == 0) {
                entry = curr;
                break;
            }
            curr = curr->next;
        }

        if (!entry) {
            entry = malloc(sizeof(MapEntry));
            if (!entry) {
                free_map(map);
                return NULL;
            }
            entry->key = my_strdup(keys[i]);
            if (!entry->key) {
                free(entry);
                free_map(map);
                return NULL;
            }
            entry->values = NULL;
            entry->next = map->head;
            map->head = entry;
        }

        ValueNode *vnode = malloc(sizeof(ValueNode));
        if (!vnode) {
            free_map(map);
            return NULL;
        }
        vnode->value = my_strdup(values[i]);
        if (!vnode->value) {
            free(vnode);
            free_map(map);
            return NULL;
        }
        vnode->next = entry->values;
        entry->values = vnode;
    }

    return map;
}

int main(void) {
    const char *keys[] = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    const char *values[] = {"1", "2", "3", "4", "5", "6"};
    size_t count = sizeof(keys) / sizeof(keys[0]);

    Map *map = group_pairs(keys, values, count);
    if (!map) {
        fprintf(stderr, "Failed to group pairs\n");
        return EXIT_FAILURE;
    }

    MapEntry *entry = map->head;
    while (entry) {
        printf("Key: %s -> Values: ", entry->key);
        ValueNode *vnode = entry->values;
        while (vnode) {
            printf("%s ", vnode->value);
            vnode = vnode->next;
        }
        printf("\n");
        entry = entry->next;
    }

    free_map(map);
    return EXIT_SUCCESS;
}