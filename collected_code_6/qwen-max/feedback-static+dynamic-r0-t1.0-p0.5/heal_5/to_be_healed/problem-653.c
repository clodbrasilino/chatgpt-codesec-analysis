#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'KeyValuePair::value' is never used. [unusedStructMember]
     */
    char *value;
} KeyValuePair;

typedef struct ListNode {
    char *value;
    struct ListNode *next;
} ListNode;

typedef struct {
    char *key;
    ListNode *head;
} ListMapEntry;

typedef struct {
    ListMapEntry **entries;
    int capacity;
    int size;
} ListMap;

ListNode* create_node(char *value) {
    ListNode *node = malloc(sizeof(ListNode));
    node->value = strdup(value);
    node->next = NULL;
    return node;
}

ListMap* create_list_map(int capacity) {
    ListMap *map = malloc(sizeof(ListMap));
    map->capacity = capacity;
    map->size = 0;
    map->entries = calloc(capacity, sizeof(ListMapEntry *));
    return map;
}

int hash_function(const char *key, int capacity) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

void insert_into_list_map(ListMap *map, const char *key, const char *value) {
    int index = hash_function(key, map->capacity);
    ListMapEntry *entry = map->entries[index];
    if (entry == NULL) {
        entry = malloc(sizeof(ListMapEntry));
        entry->key = strdup(key);
        entry->head = create_node(value);
        map->entries[index] = entry;
        map->size++;
    } else {
        ListNode *new_node = create_node(value);
        new_node->next = entry->head;
        entry->head = new_node;
    }
}

void print_list_map(ListMap *map) {
    for (int i = 0; i < map->capacity; i++) {
        ListMapEntry *entry = map->entries[i];
        if (entry != NULL) {
            printf("%s: ", entry->key);
            ListNode *current = entry->head;
            while (current != NULL) {
                printf("%s -> ", current->value);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

void free_list_map(ListMap *map) {
    for (int i = 0; i < map->capacity; i++) {
        ListMapEntry *entry = map->entries[i];
        if (entry != NULL) {
            ListNode *current = entry->head;
            while (current != NULL) {
                ListNode *temp = current;
                current = current->next;
                free(temp->value);
                free(temp);
            }
            free(entry->key);
            free(entry);
        }
    }
    free(map->entries);
    free(map);
}

int main() {
    ListMap *map = create_list_map(10);
    insert_into_list_map(map, "key1", "value1");
    insert_into_list_map(map, "key1", "value2");
    insert_into_list_map(map, "key2", "value3");
    insert_into_list_map(map, "key2", "value4");

    print_list_map(map);

    free_list_map(map);
    return 0;
}