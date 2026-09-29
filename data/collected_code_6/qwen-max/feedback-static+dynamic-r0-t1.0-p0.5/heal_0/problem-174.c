#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct {
    char *key;
    Node *head;
} ListEntry;

typedef struct {
    ListEntry **entries;
    int size;
    int capacity;
} Dictionary;

int hashFunction(const char *key, int capacity) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % capacity;
}

Dictionary *createDictionary(int capacity) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->size = 0;
    dict->capacity = capacity;
    dict->entries = (ListEntry **)calloc(capacity, sizeof(ListEntry *));
    return dict;
}

void addKeyValuePair(Dictionary *dict, const char *key, const char *value) {
    int index = hashFunction(key, dict->capacity);
    ListEntry *entry = dict->entries[index];
    if (entry == NULL) {
        entry = (ListEntry *)malloc(sizeof(ListEntry));
        entry->key = strdup(key);
        entry->head = NULL;
        dict->entries[index] = entry;
        dict->size++;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = strdup(value);
    newNode->next = entry->head;
    entry->head = newNode;
}

void printDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->capacity; i++) {
        ListEntry *entry = dict->entries[i];
        if (entry != NULL) {
            printf("%s: ", entry->key);
            Node *node = entry->head;
            while (node != NULL) {
                printf("%s -> ", node->value);
                node = node->next;
            }
            printf("NULL\n");
        }
    }
}

void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->capacity; i++) {
        ListEntry *entry = dict->entries[i];
        if (entry != NULL) {
            Node *node = entry->head;
            while (node != NULL) {
                Node *temp = node;
                node = node->next;
                free(temp->value);
                free(temp);
            }
            free(entry->key);
            free(entry);
        }
    }
    free(dict->entries);
    free(dict);
}

int main() {
    Dictionary *dict = createDictionary(10);
    addKeyValuePair(dict, "fruit", "apple");
    addKeyValuePair(dict, "fruit", "banana");
    addKeyValuePair(dict, "vegetable", "carrot");
    addKeyValuePair(dict, "vegetable", "potato");

    printDictionary(dict);

    freeDictionary(dict);
    return 0;
}