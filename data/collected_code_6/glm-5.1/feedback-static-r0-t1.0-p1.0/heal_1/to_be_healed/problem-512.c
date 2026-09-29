#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { NODE_INT, NODE_TUPLE } NodeType;

typedef struct Node {
    NodeType type;
    union {
        int value;
        struct {
            struct Node *items;
            size_t count;
        } tuple;
    };
} Node;

typedef struct {
    int key;
    size_t count;
} FreqEntry;

typedef struct {
    FreqEntry *entries;
    size_t count;
    size_t capacity;
} FreqMap;

FreqMap *create_freq_map() {
    FreqMap *map = (FreqMap *)malloc(sizeof(FreqMap));
    if (!map) return NULL;
    map->entries = (FreqEntry *)malloc(16 * sizeof(FreqEntry));
    if (!map->entries) {
        free(map);
        return NULL;
    }
    map->count = 0;
    map->capacity = 16;
    return map;
}

void free_freq_map(FreqMap *map) {
    if (map) {
        if (map->entries) free(map->entries);
        free(map);
    }
}

int insert_or_update_freq(FreqMap *map, int key) {
    for (size_t i = 0; i < map->count; i++) {
        if (map->entries[i].key == key) {
            map->entries[i].count++;
            return 0;
        }
    }
    if (map->count == map->capacity) {
        size_t new_capacity = map->capacity * 2;
        FreqEntry *new_entries = (FreqEntry *)realloc(map->entries, new_capacity * sizeof(FreqEntry));
        if (!new_entries) return -1;
        map->entries = new_entries;
        map->capacity = new_capacity;
    }
    map->entries[map->count].key = key;
    map->entries[map->count].count = 1;
    map->count++;
    return 0;
}

int count_frequency(Node *node, FreqMap *map) {
    if (!node || !map) return -1;
    if (node->type == NODE_INT) {
        return insert_or_update_freq(map, node->value);
    } else if (node->type == NODE_TUPLE) {
        for (size_t i = 0; i < node->tuple.count; i++) {
            if (count_frequency(&node->tuple.items[i], map) != 0) {
                return -1;
            }
        }
        return 0;
    }
    return -1;
}

Node create_int_node(int val) {
    Node n;
    n.type = NODE_INT;
    n.value = val;
    return n;
}

Node create_tuple_node(Node *items, size_t count) {
    Node n;
    n.type = NODE_TUPLE;
    n.tuple.items = items;
    n.tuple.count = count;
    return n;
}

void free_node(Node *node) {
    if (!node) return;
    if (node->type == NODE_TUPLE) {
        if (node->tuple.items) {
            for (size_t i = 0; i < node->tuple.count; i++) {
                free_node(&node->tuple.items[i]);
            }
            free(node->tuple.items);
            node->tuple.items = NULL;
        }
    }
}

int main() {
    Node inner_items_1[2];
    inner_items_1[0] = create_int_node(3);
    inner_items_1[1] = create_int_node(4);

    Node inner_tuple_1 = create_tuple_node(inner_items_1, 2);

    Node inner_items_2[2];
    inner_items_2[0] = create_int_node(5);
    /* Possible weaknesses found:
     *  Variable 'inner_items_2[1]' is assigned a value that is never used. [unreadVariable]
     */
    inner_items_2[1] = create_tuple_node(NULL, 0);

    Node *inner_items_2_alloc = (Node *)malloc(2 * sizeof(Node));
    if (!inner_items_2_alloc) return 1;
    inner_items_2_alloc[0] = create_int_node(5);

    Node *deep_items = (Node *)malloc(1 * sizeof(Node));
    if (!deep_items) {
        free(inner_items_2_alloc);
        return 1;
    }
    deep_items[0] = create_int_node(6);
    inner_items_2_alloc[1] = create_tuple_node(deep_items, 1);

    Node inner_tuple_2 = create_tuple_node(inner_items_2_alloc, 2);

    Node root_items[3];
    root_items[0] = create_int_node(1);
    root_items[1] = create_int_node(2);
    /* Possible weaknesses found:
     *  Variable 'root_items[2]' is assigned a value that is never used. [unreadVariable]
     */
    root_items[2] = create_int_node(3);

    Node *root_alloc = (Node *)malloc(5 * sizeof(Node));
    if (!root_alloc) {
        free_node(&inner_tuple_1);
        free_node(&inner_tuple_2);
        return 1;
    }
    root_alloc[0] = create_int_node(1);
    root_alloc[1] = create_int_node(2);
    root_alloc[2] = create_int_node(3);
    root_alloc[3] = inner_tuple_1;
    root_alloc[4] = inner_tuple_2;

    Node root = create_tuple_node(root_alloc, 5);

    FreqMap *map = create_freq_map();
    if (!map) {
        free_node(&root);
        return 1;
    }

    if (count_frequency(&root, map) != 0) {
        free_freq_map(map);
        free_node(&root);
        return 1;
    }

    for (size_t i = 0; i < map->count; i++) {
        printf("%d: %zu\n", map->entries[i].key, map->entries[i].count);
    }

    free_freq_map(map);
    free_node(&root);

    return 0;
}