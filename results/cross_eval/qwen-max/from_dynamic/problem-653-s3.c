#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct {
    char *key;
    Node *head;
} ListMapEntry;

typedef struct {
    ListMapEntry **entries;
    size_t size;
} ListMap;

ListMap* create_list_map(size_t initial_size) {
    ListMap *map = (ListMap *)malloc(sizeof(ListMap));
    if (!map) return NULL;
    map->size = initial_size;
    map->entries = (ListMapEntry **)calloc(initial_size, sizeof(ListMapEntry *));
    if (!map->entries) {
        free(map);
        return NULL;
    }
    return map;
}

void free_node(Node *node) {
    if (node) {
        free(node->key);
        free(node);
    }
}

void delete_list(Node *head) {
    Node *current = head;
    Node *next;
    while (current) {
        next = current->next;
        free_node(current);
        current = next;
    }
}

void destroy_list_map(ListMap *map) {
    for (size_t i = 0; i < map->size; ++i) {
        if (map->entries[i]) {
            delete_list(map->entries[i]->head);
            free(map->entries[i]->key);
            free(map->entries[i]);
        }
    }
    free(map->entries);
    free(map);
}

size_t hash(char *key, size_t size) {
    size_t hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

Node* create_node(const char *key, int value) {
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

void append_to_list(Node **head, const char *key, int value) {
    Node *new_node = create_node(key, value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
}

int add_to_list_map(ListMap *map, const char *key, int value) {
    size_t index = hash(key, map->size);
    ListMapEntry *entry = map->entries[index];
    if (entry == NULL) {
        entry = (ListMapEntry *)malloc(sizeof(ListMapEntry));
        if (!entry) return 1;
        entry->key = strdup(key);
        if (!entry->key) {
            free(entry);
            return 1;
        }
        entry->head = NULL;
        map->entries[index] = entry;
    } else if (strcmp(entry->key, key) != 0) {
        return 2;
    }
    append_to_list(&entry->head, key, value);
    return 0;
}

void print_list(Node *head) {
    while (head) {
        printf("%s: %d\n", head->key, head->value);
        head = head->next;
    }
}

int main() {
    ListMap *map = create_list_map(10);
    if (!map) return 1;

    char *keys[] = {"one", "two", "three", "two"};
    int values[] = {1, 2, 3, 4};

    for (int i = 0; i < 4; i++) {
        if (add_to_list_map(map, keys[i], values[i])) {
            fprintf(stderr, "Failed to add to list map.\n");
            destroy_list_map(map);
            return 1;
        }
    }

    for (size_t i = 0; i < map->size; ++i) {
        ListMapEntry *entry = map->entries[i];
        if (entry) {
            printf("Key: %s\n", entry->key);
            print_list(entry->head);
        }
    }

    destroy_list_map(map);
    return 0;
}