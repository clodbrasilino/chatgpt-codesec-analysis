#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct DictEntry {
    char *key;
    Node *head;
    struct DictEntry *next;
} DictEntry;

typedef struct {
    DictEntry *head;
} Dictionary;

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict) {
        dict->head = NULL;
    }
    return dict;
}

void add_to_dictionary(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return;

    DictEntry *current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            break;
        }
        current = current->next;
    }

    if (current == NULL) {
        current = (DictEntry*)malloc(sizeof(DictEntry));
        if (!current) return;
        
        current->key = strdup(key);
        if (!current->key) {
            free(current);
            return;
        }
        current->head = NULL;
        current->next = dict->head;
        dict->head = current;
    }

    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;
    
    new_node->value = strdup(value);
    if (!new_node->value) {
        free(new_node);
        return;
    }
    new_node->next = current->head;
    current->head = new_node;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;

    DictEntry *current_entry = dict->head;
    while (current_entry != NULL) {
        DictEntry *next_entry = current_entry->next;
        
        Node *current_node = current_entry->head;
        while (current_node != NULL) {
            Node *next_node = current_node->next;
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

void print_dictionary(Dictionary *dict) {
    if (!dict) return;

    DictEntry *current_entry = dict->head;
    while (current_entry != NULL) {
        printf("%s: [", current_entry->key);
        Node *current_node = current_entry->head;
        while (current_node != NULL) {
            printf("\"%s\"", current_node->value);
            if (current_node->next != NULL) {
                printf(", ");
            }
            current_node = current_node->next;
        }
        printf("]\n");
        current_entry = current_entry->next;
    }
}

int main() {
    Dictionary *dict = create_dictionary();
    if (!dict) {
        fprintf(stderr, "Failed to create dictionary\n");
        return 1;
    }

    add_to_dictionary(dict, "fruit", "apple");
    add_to_dictionary(dict, "fruit", "banana");
    add_to_dictionary(dict, "color", "red");
    add_to_dictionary(dict, "color", "blue");
    add_to_dictionary(dict, "fruit", "orange");

    print_dictionary(dict);

    free_dictionary(dict);

    return 0;
}