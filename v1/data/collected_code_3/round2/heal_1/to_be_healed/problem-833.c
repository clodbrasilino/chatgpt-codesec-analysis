#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct HashNode {
    char* key;
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode* buckets[TABLE_SIZE];
} HashTable;

HashTable* create_table() {
    HashTable* table = malloc(sizeof(HashTable));
    memset(table, 0, sizeof(HashTable));
    return table;
}

unsigned int hash(char* key) {
    unsigned int i, hash = 0;
    for (i = 0; key[i]; i++) {
        hash += key[i];
    }
    return hash % TABLE_SIZE;
}

void insert(HashTable* table, char* key) {
    unsigned int index = hash(key);
    HashNode* node = malloc(sizeof(HashNode));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->key = strdup(key);
    node->next = table->buckets[index];
    table->buckets[index] = node;
}

char** get_keys(HashTable* table, int* length) {
    char** keys = malloc(TABLE_SIZE * sizeof(char*));
    *length = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (HashNode* node = table->buckets[i]; node; node = node->next) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'keys' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            keys[(*length)++] = strdup(node->key);
        }
    }
    return keys;
}

int main() {
    HashTable* table = create_table();
    insert(table, "key1");
    insert(table, "key2");
    insert(table, "key3");

    int length;
    char** keys = get_keys(table, &length);

    for (int i = 0; i < length; i++) {
        printf("%s\n", keys[i]);
        free(keys[i]);
    }
    free(keys);
    free(table);

    return 0;
}