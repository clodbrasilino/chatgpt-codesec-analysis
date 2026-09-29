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
    while ((c = *key++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

Dictionary *create_dictionary(int size) {
    Dictionary *dict = NULL;
    KeyValue **buckets = NULL;
    
    if (size <= 0) {
        return NULL;
    }
    
    dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    
    buckets = (KeyValue **)calloc(size, sizeof(KeyValue *));
    if (buckets == NULL) {
        free(dict);
        return NULL;
    }
    
    dict->size = size;
    dict->buckets = buckets;
    return dict;
}

void destroy_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    
    if (dict->buckets != NULL) {
        for (int i = 0; i < dict->size; i++) {
            KeyValue *current = dict->buckets[i];
            while (current != NULL) {
                KeyValue *temp = current;
                current = current->next;
                if (temp->key != NULL) {
                    free(temp->key);
                }
                free(temp);
            }
        }
        free(dict->buckets);
    }
    free(dict);
}

int insert(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || dict->buckets == NULL || key == NULL) {
        return -1;
    }
    
    unsigned int index = hash(key, dict->size);
    KeyValue *current = dict->buckets[index];
    
    while (current != NULL) {
        if (current->key != NULL && strcmp(current->key, key) == 0) {
            current->value = value;
            return 0;
        }
        current = current->next;
    }
    
    KeyValue *new_pair = (KeyValue *)malloc(sizeof(KeyValue));
    if (new_pair == NULL) {
        return -1;
    }
    
    new_pair->key = NULL;
    new_pair->value = value;
    new_pair->next = NULL;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t key_len = strlen(key);
    if (key_len >= (size_t)-1) {
        free(new_pair);
        return -1;
    }
    
    new_pair->key = (char *)malloc(key_len + 1);
    if (new_pair->key == NULL) {
        free(new_pair);
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_pair->key, key, key_len);
    new_pair->key[key_len] = '\0';
    
    new_pair->next = dict->buckets[index];
    dict->buckets[index] = new_pair;
    return 0;
}

int get_by_index(Dictionary *dict, int index, char **key, int *value) {
    if (dict == NULL || dict->buckets == NULL || key == NULL || value == NULL || index < 0) {
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