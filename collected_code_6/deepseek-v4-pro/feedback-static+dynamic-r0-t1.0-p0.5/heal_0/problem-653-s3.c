#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    size_t size;
} Map;

static unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

Map *map_create(size_t size) {
    Map *map = malloc(sizeof(Map));
    if (!map) return NULL;
    map->size = size;
    map->buckets = calloc(size, sizeof(Node *));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    return map;
}

void map_insert(Map *map, const char *key, int value) {
    if (!map || !key) return;
    unsigned long index = hash(key) % map->size;
    Node *current = map->buckets[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            Node *new_node = malloc(sizeof(Node));
            if (!new_node) return;
            new_node->key = strdup(key);
            if (!new_node->key) {
                free(new_node);
                return;
            }
            new_node->value = value;
            new_node->next = current->next;
            current->next = new_node;
            return;
        }
        current = current->next;
    }
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return;
    new_node->key = strdup(key);
    if (!new_node->key) {
        free(new_node);
        return;
    }
    new_node->value = value;
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
}

void map_print(Map *map) {
    if (!map) return;
    for (size_t i = 0; i < map->size; i++) {
        Node *current = map->buckets[i];
        while (current) {
            printf("%s: [", current->key);
            Node *value_node = current;
            while (value_node) {
                printf("%d", value_node->value);
                if (value_node->next && strcmp(value_node->next->key, current->key) == 0) {
                    printf(", ");
                }
                value_node = value_node->next;
            }
            printf("]\n");
            while (current && strcmp(current->key, current->key) == 0) {
                current = current->next;
            }
        }
    }
}

void map_free(Map *map) {
    if (!map) return;
    for (size_t i = 0; i < map->size; i++) {
        Node *current = map->buckets[i];
        while (current) {
            Node *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
    free(map->buckets);
    free(map);
}

int main(void) {
    Map *map = map_create(10);
    if (!map) {
        fprintf(stderr, "Failed to create map\n");
        return 1;
    }

    map_insert(map, "apple", 1);
    map_insert(map, "banana", 2);
    map_insert(map, "apple", 3);
    map_insert(map, "cherry", 4);
    map_insert(map, "banana", 5);
    map_insert(map, "apple", 6);

    map_print(map);
    map_free(map);
    return 0;
}