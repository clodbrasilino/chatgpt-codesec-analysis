#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct HashTable {
    Entry **entries;
} HashTable;

HashTable* create_table() {
    HashTable *table = malloc(sizeof(HashTable));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'table' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    table->entries = malloc(sizeof(Entry*) * HASH_SIZE);
    for(int i=0; i<HASH_SIZE; i++)
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*table.entries + (long unsigned int)i * 8' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        table->entries[i] = NULL;
    return table;
}

int hash(char *key) {
    int value = 0;
    for (char *c = key; *c != '\0'; c++)
        value += *c;
    return value % HASH_SIZE;
}

void insert(HashTable *table, char *key, int value) {
    int slot = hash(key);
    Entry *entry = table->entries[slot];
    if (entry == NULL) {
        entry = malloc(sizeof(Entry));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'entry' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        entry->key = strdup(key);
        entry->value = value;
        entry->next = NULL;
        table->entries[slot] = entry;
    } else {
        while (entry != NULL) {
            if (strcmp(entry->key, key) == 0) {
                entry->value += value;
                return;
            }
            entry = entry->next;
        }
        entry = malloc(sizeof(Entry));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'entry' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        entry->key = strdup(key);
        entry->value = value;
        entry->next = table->entries[slot];
        table->entries[slot] = entry;
    }
}

void combine(HashTable *table1, HashTable *table2) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Entry *entry = table2->entries[i];
        while (entry != NULL) {
            insert(table1, entry->key, entry->value);
            entry = entry->next;
        }
    }
}

int main() {
    HashTable *table1 = create_table();
    HashTable *table2 = create_table();

    insert(table1, "apple", 1);
    insert(table1, "banana", 2);
    insert(table2, "apple", 3);
    insert(table2, "cherry", 4);

    combine(table1, table2);

    return 0;
}