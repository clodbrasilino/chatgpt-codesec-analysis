#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    char *key;
    void *value;
    struct KeyValue *next;
} KeyValue;

typedef struct {
    KeyValue *head;
    int size;
} Dictionary;

Dictionary *dict_create(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

int dict_put(Dictionary *dict, const char *key, void *value) {
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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t key_len = strlen(key);
    new_pair->key = (char *)malloc(key_len + 1);
    if (new_pair->key == NULL) {
        free(new_pair);
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(new_pair->key, key);
    new_pair->value = value;
    new_pair->next = dict->head;
    dict->head = new_pair;
    dict->size++;
    
    return 0;
}

char **dict_get_keys(Dictionary *dict, int *key_count) {
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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t key_len = strlen(current->key);
        keys[index] = (char *)malloc(key_len + 1);
        if (keys[index] == NULL) {
            for (int i = 0; i < index; i++) {
                free(keys[i]);
            }
            free(keys);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(keys[index], current->key);
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
    
    free(dict);
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
    Dictionary *dict = dict_create();
    if (dict == NULL) {
        return 1;
    }
    
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    
    dict_put(dict, "name", &value1);
    dict_put(dict, "age", &value2);
    dict_put(dict, "city", &value3);
    
    int key_count = 0;
    char **keys = dict_get_keys(dict, &key_count);
    
    if (keys != NULL) {
        for (int i = 0; i < key_count; i++) {
            printf("%s\n", keys[i]);
        }
        free_keys(keys, key_count);
    }
    
    dict_free(dict);
    
    return 0;
}