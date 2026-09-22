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
    struct MapEntry* next;
} MapEntry;

typedef struct Map {
    MapEntry* head;
} Map;

ListNode* create_list_node(const char* value) {
    if (!value) return NULL;
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (!new_node) return NULL;
    new_node->value = strdup(value);
    if (!new_node->value) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

MapEntry* create_map_entry(const char* key, const char* value) {
    if (!key || !value) return NULL;
    MapEntry* new_entry = (MapEntry*)malloc(sizeof(MapEntry));
    if (!new_entry) return NULL;
    new_entry->key = strdup(key);
    if (!new_entry->key) {
        free(new_entry);
        return NULL;
    }
    new_entry->head = create_list_node(value);
    if (!new_entry->head) {
        free(new_entry->key);
        free(new_entry);
        return NULL;
    }
    new_entry->next = NULL;
    return new_entry;
}

Map* create_map() {
    Map* map = (Map*)malloc(sizeof(Map));
    if (!map) return NULL;
    map->head = NULL;
    return map;
}

void free_list(ListNode* head) {
    ListNode* current = head;
    while (current) {
        ListNode* next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

void free_map(Map* map) {
    if (!map) return;
    MapEntry* current = map->head;
    while (current) {
        MapEntry* next = current->next;
        free(current->key);
        free_list(current->head);
        free(current);
        current = next;
    }
    free(map);
}

int add_to_map(Map* map, const char* key, const char* value) {
    if (!map || !key || !value) return -1;
    MapEntry* current = map->head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            ListNode* new_node = create_list_node(value);
            if (!new_node) return -1;
            ListNode* list_curr = current->head;
            while (list_curr->next) {
                list_curr = list_curr->next;
            }
            list_curr->next = new_node;
            return 0;
        }
        if (!current->next) break;
        current = current->next;
    }
    MapEntry* new_entry = create_map_entry(key, value);
    if (!new_entry) return -1;
    if (!map->head) {
        map->head = new_entry;
    } else {
        current->next = new_entry;
    }
    return 0;
}

Map* group_key_value_pairs(KeyValuePair* pairs, size_t count) {
    if (!pairs) return NULL;
    Map* map = create_map();
    if (!map) return NULL;
    for (size_t i = 0; i < count; ++i) {
        if (add_to_map(map, pairs[i].key, pairs[i].value) != 0) {
            free_map(map);
            return NULL;
        }
    }
    return map;
}

void print_map(Map* map) {
    if (!map) return;
    MapEntry* current_entry = map->head;
    while (current_entry) {
        printf("%s: [", current_entry->key);
        ListNode* current_node = current_entry->head;
        while (current_node) {
            printf("\"%s\"", current_node->value);
            if (current_node->next) printf(", ");
            current_node = current_node->next;
        }
        printf("]\n");
        current_entry = current_entry->next;
    }
}

int main() {
    KeyValuePair pairs[] = {
        {"Fruit", "Apple"},
        {"Fruit", "Banana"},
        {"Vegetable", "Carrot"},
        {"Fruit", "Orange"},
        {"Vegetable", "Broccoli"}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);

    Map* grouped_map = group_key_value_pairs(pairs, count);
    if (grouped_map) {
        print_map(grouped_map);
        free_map(grouped_map);
    } else {
        fprintf(stderr, "Failed to group key-value pairs.\n");
    }

    return 0;
}