#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValuePair {
    char* key;
    char* value;
} KeyValuePair;

typedef struct ListNode {
    char* value;
    struct ListNode* next;
} ListNode;

typedef struct MapEntry {
    char* key;
    ListNode* head;
    ListNode* tail;
    struct MapEntry* next;
} MapEntry;

typedef struct Map {
    MapEntry* head;
} Map;

Map* create_map() {
    Map* map = (Map*)malloc(sizeof(Map));
    if (map) {
        map->head = NULL;
    }
    return map;
}

ListNode* create_list_node(const char* value) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (node) {
        node->value = strdup(value);
        if (!node->value) {
            free(node);
            return NULL;
        }
        node->next = NULL;
    }
    return node;
}

MapEntry* create_map_entry(const char* key, const char* value) {
    MapEntry* entry = (MapEntry*)malloc(sizeof(MapEntry));
    if (entry) {
        entry->key = strdup(key);
        if (!entry->key) {
            free(entry);
            return NULL;
        }
        entry->head = create_list_node(value);
        if (!entry->head) {
            free(entry->key);
            free(entry);
            return NULL;
        }
        entry->tail = entry->head;
        entry->next = NULL;
    }
    return entry;
}

int add_to_map(Map* map, const char* key, const char* value) {
    if (!map || !key || !value) return -1;

    MapEntry* current = map->head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            ListNode* new_node = create_list_node(value);
            if (!new_node) return -1;
            current->tail->next = new_node;
            current->tail = new_node;
            return 0;
        }
        current = current->next;
    }

    MapEntry* new_entry = create_map_entry(key, value);
    if (!new_entry) return -1;
    new_entry->next = map->head;
    map->head = new_entry;
    return 0;
}

void free_map(Map* map) {
    if (!map) return;
    MapEntry* current_entry = map->head;
    while (current_entry) {
        MapEntry* next_entry = current_entry->next;
        ListNode* current_node = current_entry->head;
        while (current_node) {
            ListNode* next_node = current_node->next;
            free(current_node->value);
            free(current_node);
            current_node = next_node;
        }
        free(current_entry->key);
        free(current_entry);
        current_entry = next_entry;
    }
    free(map);
}

void print_map(Map* map) {
    if (!map) return;
    MapEntry* current_entry = map->head;
    while (current_entry) {
        printf("%s: [", current_entry->key);
        ListNode* current_node = current_entry->head;
        while (current_node) {
            printf("\"%s\"", current_node->value);
            if (current_node->next) {
                printf(", ");
            }
            current_node = current_node->next;
        }
        printf("]\n");
        current_entry = current_entry->next;
    }
}

int main() {
    KeyValuePair pairs[] = {
        {"fruit", "apple"},
        {"color", "red"},
        {"fruit", "banana"},
        {"color", "blue"},
        {"fruit", "cherry"},
        {"animal", "dog"}
    };
    size_t num_pairs = sizeof(pairs) / sizeof(pairs[0]);

    Map* map = create_map();
    if (!map) {
        fprintf(stderr, "Failed to create map\n");
        return 1;
    }

    for (size_t i = 0; i < num_pairs; ++i) {
        if (add_to_map(map, pairs[i].key, pairs[i].value) != 0) {
            fprintf(stderr, "Failed to add pair to map\n");
            free_map(map);
            return 1;
        }
    }

    print_map(map);
    free_map(map);

    return 0;
}