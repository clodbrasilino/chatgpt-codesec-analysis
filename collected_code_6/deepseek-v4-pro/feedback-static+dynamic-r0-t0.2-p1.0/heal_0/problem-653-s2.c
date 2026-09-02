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

static size_t hash(const char *key, size_t size) {
    size_t hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

static Node *create_node(const char *key, int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    node->key = strdup(key);
    if (!node->key) {
        free(node);
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

static void free_node(Node *node) {
    if (!node) return;
    free(node->key);
    free(node);
}

static void free_list(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free_node(current);
        current = next;
    }
}

Map *create_map(size_t size) {
    Map *map = (Map *)malloc(sizeof(Map));
    if (!map) return NULL;
    map->buckets = (Node **)calloc(size, sizeof(Node *));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    map->size = size;
    return map;
}

void destroy_map(Map *map) {
    if (!map) return;
    for (size_t i = 0; i < map->size; i++) {
        free_list(map->buckets[i]);
    }
    free(map->buckets);
    free(map);
}

int map_insert(Map *map, const char *key, int value) {
    if (!map || !key) return -1;
    size_t index = hash(key, map->size);
    Node *node = create_node(key, value);
    if (!node) return -1;
    node->next = map->buckets[index];
    map->buckets[index] = node;
    return 0;
}

Node *map_get_list(Map *map, const char *key) {
    if (!map || !key) return NULL;
    size_t index = hash(key, map->size);
    Node *current = map->buckets[index];
    Node *result = NULL;
    Node *tail = NULL;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            Node *copy = create_node(current->key, current->value);
            if (!copy) {
                free_list(result);
                return NULL;
            }
            if (!result) {
                result = copy;
                tail = copy;
            } else {
                tail->next = copy;
                tail = copy;
            }
        }
        current = current->next;
    }
    return result;
}

typedef struct {
    char *key;
    int value;
} Pair;

Map *group_pairs(Pair *pairs, size_t count, size_t map_size) {
    if (!pairs || count == 0 || map_size == 0) return NULL;
    Map *map = create_map(map_size);
    if (!map) return NULL;
    for (size_t i = 0; i < count; i++) {
        if (map_insert(map, pairs[i].key, pairs[i].value) != 0) {
            destroy_map(map);
            return NULL;
        }
    }
    return map;
}

int main(void) {
    Pair pairs[] = {
        {"apple", 1},
        {"banana", 2},
        {"apple", 3},
        {"cherry", 4},
        {"banana", 5},
        {"apple", 6}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);
    Map *map = group_pairs(pairs, count, 10);
    if (!map) {
        fprintf(stderr, "Failed to group pairs\n");
        return 1;
    }
    const char *keys[] = {"apple", "banana", "cherry", "date"};
    size_t num_keys = sizeof(keys) / sizeof(keys[0]);
    for (size_t i = 0; i < num_keys; i++) {
        Node *list = map_get_list(map, keys[i]);
        printf("%s: ", keys[i]);
        if (!list) {
            printf("(none)\n");
        } else {
            Node *current = list;
            while (current) {
                printf("%d ", current->value);
                current = current->next;
            }
            printf("\n");
            free_list(list);
        }
    }
    destroy_map(map);
    return 0;
}