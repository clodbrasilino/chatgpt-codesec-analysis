#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return (unsigned int)(hash % (unsigned long)size);
}

Dictionary *create_dictionary(int size) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->size = size;
    dict->buckets = (KeyValue **)calloc((size_t)size, sizeof(KeyValue *));
    if (dict->buckets == NULL) {
        free(dict);
        return NULL;
    }
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
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

int insert(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    unsigned int index = hash(key, dict->size);
    KeyValue *current = dict->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return 0;
        }
        current = current->next;
    }
    KeyValue *new_pair = (KeyValue *)malloc(sizeof(KeyValue));
    if (new_pair == NULL) {
        return -1;
    }
    size_t key_len = strnlen(key, SIZE_MAX);
    char *dup_key = strndup(key, key_len);
    if (dup_key == NULL) {
        free(new_pair);
        return -1;
    }
    new_pair->key = dup_key;
    new_pair->value = value;
    new_pair->next = dict->buckets[index];
    dict->buckets[index] = new_pair;
    return 0;
}

int get_by_index(Dictionary *dict, int index, char **key, int *value) {
    if (dict == NULL || key == NULL || value == NULL || index < 0) {
        return -1;
    }
    int count = 0;
    for (int i = 0; i < dict->size; i++) {
        KeyValue *current = dict->buckets[i];
        while (current != NULL) {
            if (count == index) {
                *key = current->key;
                *value = current->value;
                return 0;
            }
            count++;
            current = current->next;
        }
    }
    return -1;
}

int main(void) {
    Dictionary *dict = create_dictionary(10);
    if (dict == NULL) {
        return 1;
    }
    
    insert(dict, "apple", 5);
    insert(dict, "banana", 8);
    insert(dict, "cherry", 12);
    insert(dict, "date", 15);
    
    char *key = NULL;
    int value = 0;
    
    if (get_by_index(dict, 2, &key, &value) == 0) {
        printf("Index 2: %s = %d\n", key, value);
    } else {
        printf("Index 2 not found\n");
    }
    
    if (get_by_index(dict, 5, &key, &value) == 0) {
        printf("Index 5: %s = %d\n", key, value);
    } else {
        printf("Index 5 not found\n");
    }
    
    destroy_dictionary(dict);
    return 0;
}