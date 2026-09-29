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
    size_t key_len;
    char *new_key;
    
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
    
    key_len = strnlen(key, 4096);
    if (key_len >= 4096) {
        free(new_pair);
        return -1;
    }
    
    new_key = (char *)malloc(key_len + 1);
    if (new_key == NULL) {
        free(new_pair);
        return -1;
    }
    
    if (key_len + 1 <= key_len) {
        free(new_key);
        free(new_pair);
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_key, key, key_len);
    new_key[key_len] = '\0';
    
    new_pair->key = new_key;
    new_pair->value = value;
    new_pair->next = dict->head;
    dict->head = new_pair;
    dict->size++;
    
    return 0;
}

char **dict_get_keys(Dictionary *dict, int *key_count) {
    /* Possible weaknesses found:
     *  The scope of the variable 'key_len' can be reduced. [variableScope]
     */
    size_t key_len;
    
    if (dict == NULL || key_count == NULL) {
        return NULL;
    }
    
    *key_count = dict->size;
    if (dict->size == 0) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'dict->size>0' is not redundant
     */
    if (dict->size > 0 && (size_t)dict->size > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  Negative value is converted to an unsigned value
     *  Expression 'dict->size' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
     */
    char **keys = (char **)malloc(dict->size * sizeof(char *));
    if (keys == NULL) {
        return NULL;
    }
    
    KeyValue *current = dict->head;
    int index = 0;
    
    while (current != NULL && index < dict->size) {
        key_len = strnlen(current->key, 4096);
        if (key_len >= 4096) {
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
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(keys[index], current->key, key_len);
        keys[index][key_len] = '\0';
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