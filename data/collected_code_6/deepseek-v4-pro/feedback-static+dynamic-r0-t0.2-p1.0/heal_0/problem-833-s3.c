#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int dict_set(Dictionary *dict, const char *key, int value) {
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
    
    new_pair->key = (char *)malloc(strlen(key) + 1);
    if (new_pair->key == NULL) {
        free(new_pair);
        return -1;
    }
    
    strcpy(new_pair->key, key);
    new_pair->value = value;
    new_pair->next = dict->head;
    dict->head = new_pair;
    dict->size++;
    return 0;
}

char **dict_keys(Dictionary *dict, int *count) {
    if (dict == NULL || count == NULL) {
        return NULL;
    }
    
    *count = dict->size;
    if (dict->size == 0) {
        return NULL;
    }
    
    char **keys = (char **)malloc(dict->size * sizeof(char *));
    if (keys == NULL) {
        return NULL;
    }
    
    KeyValue *current = dict->head;
    int i = 0;
    while (current != NULL && i < dict->size) {
        keys[i] = (char *)malloc(strlen(current->key) + 1);
        if (keys[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(keys[j]);
            }
            free(keys);
            return NULL;
        }
        strcpy(keys[i], current->key);
        i++;
        current = current->next;
    }
    
    return keys;
}

void dict_free(Dictionary *dict) {
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
    
    dict_set(&dict, "name", 1);
    dict_set(&dict, "age", 2);
    dict_set(&dict, "city", 3);
    
    int count = 0;
    char **keys = dict_keys(&dict, &count);
    
    if (keys != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", keys[i]);
        }
        free_keys(keys, count);
    }
    
    dict_free(&dict);
    return 0;
}