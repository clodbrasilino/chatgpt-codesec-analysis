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

Dictionary *create_dictionary(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
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

int dict_get(Dictionary *dict, const char *key, int *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return -1;
    }
    
    KeyValue *current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            *value = current->value;
            return 0;
        }
        current = current->next;
    }
    
    return -1;
}

Dictionary *merge_dictionaries(Dictionary *dict1, Dictionary *dict2) {
    if (dict1 == NULL || dict2 == NULL) {
        return NULL;
    }
    
    Dictionary *merged = create_dictionary();
    if (merged == NULL) {
        return NULL;
    }
    
    KeyValue *current = dict1->head;
    while (current != NULL) {
        if (dict_put(merged, current->key, current->value) != 0) {
            free_dictionary(merged);
            return NULL;
        }
        current = current->next;
    }
    
    current = dict2->head;
    while (current != NULL) {
        if (dict_put(merged, current->key, current->value) != 0) {
            free_dictionary(merged);
            return NULL;
        }
        current = current->next;
    }
    
    return merged;
}

void free_dictionary(Dictionary *dict) {
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

void print_dictionary(Dictionary *dict) {
    if (dict == NULL) {
        printf("Dictionary is NULL\n");
        return;
    }
    
    KeyValue *current = dict->head;
    while (current != NULL) {
        printf("%s: %d\n", current->key, current->value);
        current = current->next;
    }
}

int main(void) {
    Dictionary *dict1 = create_dictionary();
    Dictionary *dict2 = create_dictionary();
    
    if (dict1 == NULL || dict2 == NULL) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }
    
    dict_put(dict1, "apple", 5);
    dict_put(dict1, "banana", 3);
    dict_put(dict1, "cherry", 8);
    
    dict_put(dict2, "banana", 10);
    dict_put(dict2, "date", 7);
    dict_put(dict2, "elderberry", 2);
    
    Dictionary *merged = merge_dictionaries(dict1, dict2);
    if (merged == NULL) {
        free_dictionary(dict1);
        free_dictionary(dict2);
        return 1;
    }
    
    printf("Merged dictionary:\n");
    print_dictionary(merged);
    
    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(merged);
    
    return 0;
}