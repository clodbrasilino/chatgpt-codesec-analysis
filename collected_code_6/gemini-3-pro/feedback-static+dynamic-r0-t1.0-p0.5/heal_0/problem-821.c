#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} Dictionary;

Dictionary* create_dictionary(void) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) {
        exit(EXIT_FAILURE);
    }
    dict->head = NULL;
    return dict;
}

void add_item(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) {
        return;
    }

    Node *current = dict->head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            char *new_val = strdup(value);
            if (!new_val) {
                exit(EXIT_FAILURE);
            }
            free(current->value);
            current->value = new_val;
            return;
        }
        current = current->next;
    }

    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    
    if (!new_node->key || !new_node->value) {
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        exit(EXIT_FAILURE);
    }

    new_node->next = dict->head;
    dict->head = new_node;
}

Dictionary* merge_dictionaries(Dictionary *dict1, Dictionary *dict2) {
    if (!dict1 || !dict2) {
        return NULL;
    }

    Dictionary *merged = create_dictionary();

    Node *current = dict1->head;
    while (current) {
        add_item(merged, current->key, current->value);
        current = current->next;
    }

    current = dict2->head;
    while (current) {
        add_item(merged, current->key, current->value);
        current = current->next;
    }

    return merged;
}

void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    Node *current = dict->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
    free(dict);
}

void print_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    Node *current = dict->head;
    while (current) {
        printf("%s: %s\n", current->key, current->value);
        current = current->next;
    }
}

int main(void) {
    Dictionary *dict1 = create_dictionary();
    Dictionary *dict2 = create_dictionary();

    add_item(dict1, "host", "127.0.0.1");
    add_item(dict1, "port", "8080");

    add_item(dict2, "port", "443");
    add_item(dict2, "protocol", "https");

    Dictionary *merged = merge_dictionaries(dict1, dict2);

    print_dictionary(merged);

    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(merged);

    return EXIT_SUCCESS;
}