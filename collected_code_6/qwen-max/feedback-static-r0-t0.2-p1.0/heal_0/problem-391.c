#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    struct Node *value;
    struct Node *next;
} Node;

typedef struct Dictionary {
    Node *head;
} Dictionary;

Node* create_node(char *key, char *value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = value ? (Node *)strdup(value) : NULL;
    new_node->next = NULL;
    return new_node;
}

void add_to_dict(Dictionary *dict, char *key, char *value) {
    Node *new_node = create_node(key, value);
    if (dict->head == NULL) {
        dict->head = new_node;
    } else {
        Node *current = dict->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

Dictionary* list_to_nested_dict(char **keys, char **values, int length) {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    dict->head = NULL;
    for (int i = 0; i < length; i++) {
        add_to_dict(dict, keys[i], values[i]);
    }
    return dict;
}

void print_dict(Dictionary *dict, int depth) {
    Node *current = dict->head;
    while (current != NULL) {
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
        printf("%s: ", current->key);
        if (current->value) {
            printf("%s\n", (char *)current->value);
        } else {
            printf("\n");
        }
        current = current->next;
    }
}

void free_dict(Dictionary *dict) {
    Node *current = dict->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->key);
        if (temp->value) {
            free(temp->value);
        }
        free(temp);
    }
    free(dict);
}

int main() {
    char *keys[] = {"a", "b", "c"};
    char *values[] = {"1", "2", "3"};
    int length = 3;

    Dictionary *dict = list_to_nested_dict(keys, values, length);
    print_dict(dict, 0);

    free_dict(dict);
    return 0;
}