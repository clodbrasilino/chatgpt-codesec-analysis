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
    ListNode* values;
    struct MapEntry* next;
} MapEntry;

typedef struct Map {
    MapEntry* head;
} Map;

ListNode* create_list_node(const char* value) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) return NULL;
    node->value = strdup(value);
    if (!node->value) {
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

MapEntry* create_map_entry(const char* key, const char* value) {
    MapEntry* entry = (MapEntry*)malloc(sizeof(MapEntry));
    if (!entry) return NULL;
    entry->key = strdup(key);
    if (!entry->key) {
        free(entry);
        return NULL;
    }
    entry->values = create_list_node(value);
    if (!entry->values) {
        free(entry->key);
        free(entry);
        return NULL;
    }
    entry->next = NULL;
    return entry;
}

Map* create_map() {
    Map* map = (Map*)malloc(sizeof(Map));
    if (!map) return NULL;
    map->head = NULL;
    return map;
}

int add_to_map(Map* map, const char* key, const char* value) {
    if (!map || !key || !value) return -1;

    MapEntry* current = map->head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            ListNode* new_node = create_list_node(value);
            if (!new_node) return -1;
            ListNode* tail = current->values;
            while (tail->next) {
                tail = tail->next;
            }
            tail->next = new_node;
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

Map* group_key_value_pairs(KeyValuePair* pairs, size_t count) {
    if (!pairs) return NULL;

    Map* map = create_map();
    if (!map) return NULL;

    for (size_t i = 0; i < count; ++i) {
        if (add_to_map(map, pairs[i].key, pairs[i].value) != 0) {
            return NULL;
        }
    }

    return map;
}

void free_map(Map* map) {
    if (!map) return;

    MapEntry* current_entry = map->head;
    while (current_entry) {
        MapEntry* next_entry = current_entry->next;
        
        ListNode* current_node = current_entry->values;
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
        ListNode* current_node = current_entry->values;
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
        {"fruit", "orange"}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);

    Map* grouped_map = group_key_value_pairs(pairs, count);
    if (grouped_map) {
        print_map(grouped_map);
        free_map(grouped_map);
    } else {
        fprintf(stderr, "Failed to group key-value pairs.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}