#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    char *key;
    int value;
    struct KeyValue *next;
} KeyValue;

typedef struct {
    KeyValue **buckets;
    int size;
} Dictionary;

unsigned int hash(const char *key, int size) {
    unsigned int hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

Dictionary *create_dictionary(int size) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->size = size;
    dict->buckets = (KeyValue **)calloc(size, sizeof(KeyValue *));
    if (dict->buckets == NULL) {
        free(dict);
        return NULL;
    }
    return dict;
}

void insert(Dictionary *dict, const char *key, int value) {
    unsigned int index = hash(key, dict->size);
    KeyValue *new_pair = (KeyValue *)malloc(sizeof(KeyValue));
    if (new_pair == NULL) {
        return;
    }
    new_pair->key = (char *)malloc(strlen(key) + 1);
    if (new_pair->key == NULL) {
        free(new_pair);
        return;
    }
    strcpy(new_pair->key, key);
    new_pair->value = value;
    new_pair->next = dict->buckets[index];
    dict->buckets[index] = new_pair;
}

int get_by_index(Dictionary *dict, int index) {
    if (dict == NULL || index < 0 || index >= dict->size) {
        return -1;
    }
    const KeyValue *current = dict->buckets[index];
    if (current == NULL) {
        return -1;
    }
    return current->value;
}

void free_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    for (int i = 0; i < dict->size; i++) {
        KeyValue *current = dict->buckets[i];
        while (current != NULL) {
            KeyValue *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(dict->buckets);
    free(dict);
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (dict == NULL) {
        return 1;
    }

    insert(dict, "apple", 100);
    insert(dict, "banana", 200);
    insert(dict, "cherry", 300);

    int index = hash("apple", dict->size);
    int value = get_by_index(dict, index);
    printf("Value at index %d: %d\n", index, value);

    free_dictionary(dict);
    return 0;
}