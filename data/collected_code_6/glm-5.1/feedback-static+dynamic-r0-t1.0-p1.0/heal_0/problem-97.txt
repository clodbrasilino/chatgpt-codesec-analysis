#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

unsigned long hash_int(int key) {
    unsigned long hash = (unsigned long)key;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
    hash = (hash >> 16) ^ hash;
    return hash;
}

typedef struct Entry {
    int key;
    int count;
    struct Entry *next;
} Entry;

typedef struct {
    Entry **buckets;
    int size;
} HashMap;

HashMap *create_hashmap(int size) {
    HashMap *map = malloc(sizeof(HashMap));
    map->size = size;
    map->buckets = calloc(size, sizeof(Entry *));
    return map;
}

void insert_hashmap(HashMap *map, int key) {
    if (!map) return;
    unsigned long h = hash_int(key);
    int index = h % map->size;
    Entry *current = map->buckets[index];
    while (current) {
        if (current->key == key) {
            current->count++;
            return;
        }
        current = current->next;
    }
    Entry *entry = malloc(sizeof(Entry));
    entry->key = key;
    entry->count = 1;
    entry->next = map->buckets[index];
    map->buckets[index] = entry;
}

void free_hashmap(HashMap *map) {
    if (!map) return;
    for (int i = 0; i < map->size; i++) {
        Entry *current = map->buckets[i];
        while (current) {
            Entry *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}

HashMap *find_frequency(List **lists, int num_lists) {
    HashMap *map = create_hashmap(1024);
    for (int i = 0; i < num_lists; i++) {
        Node *current = lists[i]->head;
        while (current) {
            insert_hashmap(map, *(int *)current->data);
            current = current->next;
        }
    }
    return map;
}

List *create_list() {
    List *list = malloc(sizeof(List));
    list->head = NULL;
    return list;
}

void append_list(List *list, int val) {
    int *data = malloc(sizeof(int));
    *data = val;
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (!list->head) {
        list->head = node;
        return;
    }
    Node *current = list->head;
    while (current->next) {
        current = current->next;
    }
    current->next = node;
}

void free_list(List *list) {
    if (!list) return;
    Node *current = list->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    free(list);
}

int main() {
    List *lists[3];
    for (int i = 0; i < 3; i++) {
        lists[i] = create_list();
    }

    append_list(lists[0], 1);
    append_list(lists[0], 2);
    append_list(lists[0], 3);

    append_list(lists[1], 2);
    append_list(lists[1], 2);
    append_list(lists[1], 4);

    append_list(lists[2], 1);
    append_list(lists[2], 5);

    HashMap *map = find_frequency(lists, 3);

    for (int i = 0; i < map->size; i++) {
        Entry *current = map->buckets[i];
        while (current) {
            printf("%d: %d\n", current->key, current->count);
            current = current->next;
        }
    }

    free_hashmap(map);
    for (int i = 0; i < 3; i++) {
        free_list(lists[i]);
    }

    return 0;
}