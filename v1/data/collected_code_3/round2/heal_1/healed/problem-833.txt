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
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL){
        return NULL;
    }
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

int insert(HashTable* table, char* key) {
    unsigned int index = hash(key);
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    /*Check if malloc was successful*/
    if (node == NULL){
        return -1;
    }
    node->key = strdup(key);
    node->next = table->buckets[index];
    table->buckets[index] = node;
    return 0;
}

char** get_keys(HashTable* table, int* length) {
    char** keys = (char**)malloc(TABLE_SIZE * sizeof(char*));
    /*Check if malloc was successful*/
    if (keys == NULL){
        return NULL;
    }
    *length = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (HashNode* node = table->buckets[i]; node; node = node->next) {
            keys[(*length)++] = strdup(node->key);
        }
    }
    return keys;
}

int main() {
    HashTable* table = create_table();
    if (table == NULL) {
        return EXIT_FAILURE;
    }
    if(insert(table, "key1") != 0){
        return EXIT_FAILURE;
    }
    if(insert(table, "key2") != 0){
        return EXIT_FAILURE;
    }
    if(insert(table, "key3") != 0){
        return EXIT_FAILURE;
    }

    int length;
    char** keys = get_keys(table, &length);
    if (keys == NULL){
        return EXIT_FAILURE;
    }

    for (int i = 0; i < length; i++) {
        printf("%s\n", keys[i]);
        free(keys[i]);
    }
    free(keys);
    free(table);

    return EXIT_SUCCESS;
}