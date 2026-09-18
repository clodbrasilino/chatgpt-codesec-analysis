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

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

DictEntry* create_dict_entry(const char* key, int value) {
    DictEntry* new_entry = (DictEntry*)malloc(sizeof(DictEntry));
    if (!new_entry) {
        exit(EXIT_FAILURE);
    }
    new_entry->key = strdup(key);
    if (!new_entry->key) {
        free(new_entry);
        exit(EXIT_FAILURE);
    }
    new_entry->head = create_node(value);
    new_entry->next = NULL;
    return new_entry;
}

void add_to_dict(Dictionary* dict, const char* key, int value) {
    if (!dict || !key) {
        return;
    }

    DictEntry* current = dict->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            Node* new_node = create_node(value);
            new_node->next = current->head;
            current->head = new_node;
            return;
        }
        current = current->next;
    }

    DictEntry* new_entry = create_dict_entry(key, value);
    new_entry->next = dict->head;
    dict->head = new_entry;
}

void free_dictionary(Dictionary* dict) {
    if (!dict) {
        return;
    }

    DictEntry* current_entry = dict->head;
    while (current_entry != NULL) {
        DictEntry* next_entry = current_entry->next;
        
        Node* current_node = current_entry->head;
        while (current_node != NULL) {
            Node* next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
        
        free(current_entry->key);
        free(current_entry);
        current_entry = next_entry;
    }
    dict->head = NULL;
}

void print_dictionary(const Dictionary* dict) {
    if (!dict) {
        return;
    }

    DictEntry* current_entry = dict->head;
    while (current_entry != NULL) {
        printf("%s: [", current_entry->key);
        Node* current_node = current_entry->head;
        while (current_node != NULL) {
            printf("%d", current_node->value);
            if (current_node->next != NULL) {
                printf(", ");
            }
            current_node = current_node->next;
        }
        printf("]\n");
        current_entry = current_entry->next;
    }
}

int main(void) {
    Dictionary dict = {NULL};

    add_to_dict(&dict, "apple", 1);
    add_to_dict(&dict, "banana", 2);
    add_to_dict(&dict, "apple", 3);
    add_to_dict(&dict, "orange", 4);
    add_to_dict(&dict, "banana", 5);
    add_to_dict(&dict, "apple", 6);

    print_dictionary(&dict);

    free_dictionary(&dict);

    return 0;
}