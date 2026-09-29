#include <stdio.h>
#include <stdlib.h>

typedef struct ValueNode {
    int value;
    struct ValueNode *next;
} ValueNode;

typedef struct MapEntry {
    int key;
    ValueNode *values;
    struct MapEntry *next;
} MapEntry;

typedef struct Map {
    MapEntry **buckets;
    size_t capacity;
} Map;

Map *create_map(size_t capacity) {
    Map *map = malloc(sizeof(Map));
    if (!map) {
        return NULL;
    }
    map->buckets = calloc(capacity, sizeof(MapEntry *));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    map->capacity = capacity;
    return map;
}

int map_insert(Map *map, int key, int value) {
    if (!map) {
        return 0;
    }
    size_t index = ((size_t)(unsigned int)key) % map->capacity;
    
    MapEntry *entry = map->buckets[index];
    while (entry) {
        if (entry->key == key) {
            break;
        }
        entry = entry->next;
    }
    
    if (!entry) {
        entry = malloc(sizeof(MapEntry));
        if (!entry) {
            return 0;
        }
        entry->key = key;
        entry->values = NULL;
        entry->next = map->buckets[index];
        map->buckets[index] = entry;
    }
    
    ValueNode *vnode = malloc(sizeof(ValueNode));
    if (!vnode) {
        return 0;
    }
    vnode->value = value;
    vnode->next = entry->values;
    entry->values = vnode;
    
    return 1;
}

void free_map(Map *map) {
    if (!map) {
        return;
    }
    for (size_t i = 0; i < map->capacity; i++) {
        MapEntry *entry = map->buckets[i];
        while (entry) {
            MapEntry *next_entry = entry->next;
            ValueNode *vnode = entry->values;
            while (vnode) {
                ValueNode *next_vnode = vnode->next;
                free(vnode);
                vnode = next_vnode;
            }
            free(entry);
            entry = next_entry;
        }
    }
    free(map->buckets);
    free(map);
}

int main(void) {
    Map *map = create_map(16);
    if (!map) {
        return EXIT_FAILURE;
    }
    
    map_insert(map, 1, 10);
    map_insert(map, 2, 20);
    map_insert(map, 1, 30);
    map_insert(map, 3, 40);
    map_insert(map, 2, 50);
    
    for (size_t i = 0; i < map->capacity; i++) {
        MapEntry *entry = map->buckets[i];
        while (entry) {
            printf("Key: %d, Values: ", entry->key);
            ValueNode *vnode = entry->values;
            while (vnode) {
                printf("%d ", vnode->value);
                vnode = vnode->next;
            }
            printf("\n");
            entry = entry->next;
        }
    }
    
    free_map(map);
    return EXIT_SUCCESS;
}