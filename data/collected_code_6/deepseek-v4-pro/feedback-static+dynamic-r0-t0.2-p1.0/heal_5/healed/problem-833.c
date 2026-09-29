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
    KeyValue *head;
    int size;
} Dictionary;

void dict_init(Dictionary *dict) {
    dict->head = NULL;
    dict->size = 0;
}

int dict_put(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL) {
        return -1;
    }
    
    KeyValue *current = dict->head;
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
    
    size_t key_len = strlen(key);
    
    new_pair->key = (char *)malloc(key_len + 1);
    if (new_pair->key == NULL) {
        free(new_pair);
        return -1;
    }
    
    if (key_len + 1 <= key_len) {
        free(new_pair->key);
        free(new_pair);
        return -1;
    }
    
    if (key_len >= SIZE_MAX - 1) {
        free(new_pair->key);
        free(new_pair);
        return -1;
    }
    
    memcpy(new_pair->key, key, key_len + 1);
    new_pair->value = value;
    new_pair->next = dict->head;
    dict->head = new_pair;
    dict->size++;
    return 0;
}

char **dict_keys(Dictionary *dict, int *key_count) {
    if (dict == NULL || key_count == NULL) {
        return NULL;
    }
    
    *key_count = dict->size;
    if (dict->size == 0) {
        return NULL;
    }
    
    char **keys = (char **)malloc(dict->size * sizeof(char *));
    if (keys == NULL) {
        return NULL;
    }
    
    KeyValue *current = dict->head;
    int index = 0;
    while (current != NULL && index < dict->size) {
        if (current->key == NULL) {
            for (int i = 0; i < index; i++) {
                free(keys[i]);
            }
            free(keys);
            return NULL;
        }
        
        size_t key_len = strlen(current->key);
        
        if (key_len >= SIZE_MAX - 1) {
            for (int i = 0; i < index; i++) {
                free(keys[i]);
            }
            free(keys);
            return NULL;
        }
        
        keys[index] = (char *)malloc(key_len + 1);
        if (keys[index] == NULL) {
            for (int i = 0; i < index; i++) {
                free(keys[i]);
            }
            free(keys);
            return NULL;
        }
        
        if (key_len + 1 <= key_len) {
            free(keys[index]);
            for (int i = 0; i < index; i++) {
                free(keys[i]);
            }
            free(keys);
            return NULL;
        }
        
        memcpy(keys[index], current->key, key_len + 1);
        index++;
        current = current->next;
    }
    
    return keys;
}

void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    KeyValue *current = dict->head;
    while (current != NULL) {
        KeyValue *next = current->next;
        free(current->key);
        free(current);
        current = next;
    }
    dict->head = NULL;
    dict->size = 0;
}

void free_keys(char **keys, int count) {
    if (keys == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(keys[i]);
    }
    free(keys);
}

int main(void) {
    Dictionary dict;
    dict_init(&dict);
    
    dict_put(&dict, "apple", 1);
    dict_put(&dict, "banana", 2);
    dict_put(&dict, "cherry", 3);
    
    int key_count = 0;
    char **keys = dict_keys(&dict, &key_count);
    
    if (keys != NULL) {
        for (int i = 0; i < key_count; i++) {
            printf("%s\n", keys[i]);
        }
        free_keys(keys, key_count);
    }
    
    dict_free(&dict);
    return 0;
}