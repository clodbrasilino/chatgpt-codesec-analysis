#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

typedef struct HashTable {
    List **buckets;
    int size;
} HashTable;

Node* create_node(const char *key, int value) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

List* create_list() {
    List *list = (List*) malloc(sizeof(List));
    list->head = NULL;
    return list;
}

HashTable* create_hash_table(int size) {
    HashTable *table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->buckets = (List**) calloc(size, sizeof(List*));
    for (int i = 0; i < size; ++i) {
        table->buckets[i] = create_list();
    }
    return table;
}

unsigned long hash(const char *str, int size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % size;
}

void add_to_hash_table(HashTable *table, const char *key, int value) {
    unsigned long index = hash(key, table->size);
    Node *new_node = create_node(key, value);
    new_node->next = table->buckets[index]->head;
    table->buckets[index]->head = new_node;
}

void free_list(List *list) {
    Node *current = list->head;
    Node *temp;
    while (current != NULL) {
        temp = current->next;
        free(current->key);
        free(current);
        current = temp;
    }
    free(list);
}

void free_hash_table(HashTable *table) {
    if (table == NULL) return;
    for (int i = 0; i < table->size; ++i) {
        free_list(table->buckets[i]);
    }
    free(table->buckets);
    free(table);
}

void print_hash_table(HashTable *table) {
    for (int i = 0; i < table->size; ++i) {
        Node *current = table->buckets[i]->head;
        printf("Bucket %d: ", i);
        while (current != NULL) {
            printf("%s -> %d", current->key, current->value);
            if (current->next != NULL) {
                printf(", ");
            }
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    const int hash_table_size = 10;
    HashTable *table = create_hash_table(hash_table_size);

    add_to_hash_table(table, "apple", 5);
    add_to_hash_table(table, "banana", 3);
    add_to_hash_table(table, "orange", 4);
    add_to_hash_table(table, "apple", 7);
    add_to_hash_table(table, "banana", 2);

    print_hash_table(table);

    free_hash_table(table);
    return 0;
}