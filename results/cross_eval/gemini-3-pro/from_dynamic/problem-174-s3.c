#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* value;
    struct Node* next;
} Node;

typedef struct DictEntry {
    char* key;
    Node* head;
    Node* tail;
    struct DictEntry* next;
} DictEntry;

typedef struct {
    DictEntry* head;
} Dictionary;

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

Node* create_node(const char* value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;
    
    new_node->value = strdup(value);
    if (!new_node->value) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

DictEntry* create_dict_entry(const char* key, const char* value) {
    DictEntry* entry = (DictEntry*)malloc(sizeof(DictEntry));
    if (!entry) return NULL;
    
    entry->key = strdup(key);
    if (!entry->key) {
        free(entry);
        return NULL;
    }
    
    Node* val_node = create_node(value);
    if (!val_node) {
        free(entry->key);
        free(entry);
        return NULL;
    }
    
    entry->head = val_node;
    entry->tail = val_node;
    entry->next = NULL;
    return entry;
}

Dictionary* group_by_key(KeyValuePair* pairs, size_t count) {
    if (!pairs) return NULL;
    
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->head = NULL;
    
    for (size_t i = 0; i < count; i++) {
        if (!pairs[i].key || !pairs[i].value) continue;
        
        DictEntry* current = dict->head;
        int found = 0;
        
        while (current) {
            if (strcmp(current->key, pairs[i].key) == 0) {
                Node* new_node = create_node(pairs[i].value);
                if (new_node) {
                    current->tail->next = new_node;
                    current->tail = new_node;
                }
                found = 1;
                break;
            }
            current = current->next;
        }
        
        if (!found) {
            DictEntry* new_entry = create_dict_entry(pairs[i].key, pairs[i].value);
            if (new_entry) {
                new_entry->next = dict->head;
                dict->head = new_entry;
            }
        }
    }
    
    return dict;
}

void free_dictionary(Dictionary* dict) {
    if (!dict) return;
    
    DictEntry* current_entry = dict->head;
    while (current_entry) {
        DictEntry* next_entry = current_entry->next;
        
        Node* current_node = current_entry->head;
        while (current_node) {
            Node* next_node = current_node->next;
            free(current_node->value);
            free(current_node);
            current_node = next_node;
        }
        
        free(current_entry->key);
        free(current_entry);
        current_entry = next_entry;
    }
    
    free(dict);
}

void print_dictionary(Dictionary* dict) {
    if (!dict) return;
    
    DictEntry* current_entry = dict->head;
    while (current_entry) {
        printf("%s: [", current_entry->key);
        Node* current_node = current_entry->head;
        while (current_node) {
            printf("'%s'", current_node->value);
            if (current_node->next) printf(", ");
            current_node = current_node->next;
        }
        printf("]\n");
        current_entry = current_entry->next;
    }
}

int main(void) {
    KeyValuePair pairs[] = {
        {"fruit", "apple"},
        {"animal", "dog"},
        {"fruit", "banana"},
        {"color", "red"},
        {"animal", "cat"},
        {"fruit", "orange"}
    };
    
    size_t count = sizeof(pairs) / sizeof(pairs[0]);
    
    Dictionary* dict = group_by_key(pairs, count);
    if (dict) {
        print_dictionary(dict);
        free_dictionary(dict);
    }
    
    return 0;
}