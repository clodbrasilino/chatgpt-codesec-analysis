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

Dictionary *create_dictionary(void) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->head = NULL;
    return dict;
}

void insert(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) return;
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return;
    new_node->key = malloc(strlen(key) + 1);
    new_node->value = malloc(strlen(value) + 1);
    if (!new_node->key || !new_node->value) {
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return;
    }
    strcpy(new_node->key, key);
    strcpy(new_node->value, value);
    new_node->next = dict->head;
    dict->head = new_node;
}

void sort_dictionary(Dictionary *dict) {
    if (!dict || !dict->head || !dict->head->next) return;
    Node *sorted = NULL;
    Node *current = dict->head;
    while (current) {
        Node *next = current->next;
        if (!sorted || strcmp(current->key, sorted->key) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;
            while (temp->next && strcmp(temp->next->key, current->key) < 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    dict->head = sorted;
}

void print_dictionary(const Dictionary *dict) {
    if (!dict) return;
    Node *current = dict->head;
    while (current) {
        printf("%s: %s\n", current->key, current->value);
        current = current->next;
    }
}

void free_dictionary(Dictionary *dict) {
    if (!dict) return;
    Node *current = dict->head;
    while (current) {
        Node *next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    free(dict);
}

int main(void) {
    Dictionary *dict = create_dictionary();
    if (!dict) return 1;
    insert(dict, "banana", "fruit");
    insert(dict, "apple", "fruit");
    insert(dict, "cherry", "fruit");
    insert(dict, "date", "fruit");
    sort_dictionary(dict);
    print_dictionary(dict);
    free_dictionary(dict);
    return 0;
}