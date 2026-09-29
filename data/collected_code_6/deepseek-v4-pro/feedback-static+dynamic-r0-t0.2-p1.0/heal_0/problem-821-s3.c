#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictEntry {
    char *key;
    char *value;
    struct DictEntry *next;
} DictEntry;

typedef struct {
    DictEntry *head;
    int size;
} Dictionary;

Dictionary *create_dict(void) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

void dict_insert(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return;
    }
    
    DictEntry *current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = (char *)malloc(strlen(value) + 1);
            if (current->value != NULL) {
                strcpy(current->value, value);
            }
            return;
        }
        current = current->next;
    }
    
    DictEntry *new_entry = (DictEntry *)malloc(sizeof(DictEntry));
    if (new_entry == NULL) {
        return;
    }
    
    new_entry->key = (char *)malloc(strlen(key) + 1);
    new_entry->value = (char *)malloc(strlen(value) + 1);
    
    if (new_entry->key == NULL || new_entry->value == NULL) {
        free(new_entry->key);
        free(new_entry->value);
        free(new_entry);
        return;
    }
    
    strcpy(new_entry->key, key);
    strcpy(new_entry->value, value);
    new_entry->next = dict->head;
    dict->head = new_entry;
    dict->size++;
}

Dictionary *merge_dicts(Dictionary *dict1, Dictionary *dict2) {
    if (dict1 == NULL || dict2 == NULL) {
        return NULL;
    }
    
    Dictionary *merged = create_dict();
    if (merged == NULL) {
        return NULL;
    }
    
    DictEntry *current = dict1->head;
    while (current != NULL) {
        dict_insert(merged, current->key, current->value);
        current = current->next;
    }
    
    current = dict2->head;
    while (current != NULL) {
        dict_insert(merged, current->key, current->value);
        current = current->next;
    }
    
    return merged;
}

void print_dict(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    
    DictEntry *current = dict->head;
    while (current != NULL) {
        printf("%s: %s\n", current->key, current->value);
        current = current->next;
    }
}

void free_dict(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    
    DictEntry *current = dict->head;
    while (current != NULL) {
        DictEntry *temp = current;
        current = current->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
    
    free(dict);
}

int main(void) {
    Dictionary *dict1 = create_dict();
    Dictionary *dict2 = create_dict();
    Dictionary *merged = NULL;
    
    if (dict1 == NULL || dict2 == NULL) {
        free_dict(dict1);
        free_dict(dict2);
        return 1;
    }
    
    dict_insert(dict1, "name", "Alice");
    dict_insert(dict1, "age", "30");
    dict_insert(dict1, "city", "New York");
    
    dict_insert(dict2, "country", "USA");
    dict_insert(dict2, "age", "31");
    dict_insert(dict2, "occupation", "Engineer");
    
    merged = merge_dicts(dict1, dict2);
    if (merged == NULL) {
        free_dict(dict1);
        free_dict(dict2);
        return 1;
    }
    
    printf("Merged Dictionary:\n");
    print_dict(merged);
    
    free_dict(dict1);
    free_dict(dict2);
    free_dict(merged);
    
    return 0;
}