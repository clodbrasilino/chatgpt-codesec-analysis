#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct DictEntry {
    char* key;
    Node* head;
    struct DictEntry* next;
} DictEntry;

typedef struct {
    DictEntry* head;
} Dictionary;

typedef struct {
    char* key;
    int value;
} KeyValuePair;

Dictionary* create_dictionary(void) {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict != NULL) {
        dict->head = NULL;
    }
    return dict;
}

DictEntry* find_entry(Dictionary* dict, const char* key) {
    if (dict == NULL || key == NULL) return NULL;
    
    DictEntry* current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int add_to_dictionary(Dictionary* dict, const char* key, int value) {
    if (dict == NULL || key == NULL) return -1;

    DictEntry* entry = find_entry(dict, key);
    if (entry == NULL) {
        entry = (DictEntry*)malloc(sizeof(DictEntry));
        if (entry == NULL) return -1;
        
        entry->key = strdup(key);
        if (entry->key == NULL) {
            free(entry);
            return -1;
        }
        
        entry->head = NULL;
        entry->next = dict->head;
        dict->head = entry;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) return -1;
    
    new_node->value = value;
    new_node->next = entry->head;
    entry->head = new_node;

    return 0;
}

Dictionary* group_key_value_pairs(KeyValuePair* pairs, size_t count) {
    if (pairs == NULL && count > 0) return NULL;

    Dictionary* dict = create_dictionary();
    if (dict == NULL) return NULL;

    for (size_t i = 0; i < count; ++i) {
        if (add_to_dictionary(dict, pairs[i].key, pairs[i].value) != 0) {
            DictEntry* current = dict->head;
            while (current != NULL) {
                DictEntry* next_entry = current->next;
                Node* current_node = current->head;
                while (current_node != NULL) {
                    Node* next_node = current_node->next;
                    free(current_node);
                    current_node = next_node;
                }
                free(current->key);
                free(current);
                current = next_entry;
            }
            free(dict);
            return NULL;
        }
    }

    return dict;
}

void print_dictionary(Dictionary* dict) {
    if (dict == NULL) return;

    DictEntry* current = dict->head;
    while (current != NULL) {
        printf("%s: [", current->key);
        Node* current_node = current->head;
        while (current_node != NULL) {
            printf("%d", current_node->value);
            if (current_node->next != NULL) {
                printf(", ");
            }
            current_node = current_node->next;
        }
        printf("]\n");
        current = current->next;
    }
}

void free_dictionary(Dictionary* dict) {
    if (dict == NULL) return;

    DictEntry* current = dict->head;
    while (current != NULL) {
        DictEntry* next_entry = current->next;
        Node* current_node = current->head;
        while (current_node != NULL) {
            Node* next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
        free(current->key);
        free(current);
        current = next_entry;
    }
    free(dict);
}

int main(void) {
    KeyValuePair pairs[] = {
        {"apple", 1},
        {"banana", 2},
        {"apple", 3},
        {"orange", 4},
        {"banana", 5}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);

    Dictionary* dict = group_key_value_pairs(pairs, count);
    if (dict != NULL) {
        print_dictionary(dict);
        free_dictionary(dict);
    } else {
        printf("Failed to group key-value pairs.\n");
    }

    return 0;
}