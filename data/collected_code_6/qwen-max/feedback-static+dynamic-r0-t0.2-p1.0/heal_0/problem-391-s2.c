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
    if (new_node == NULL) return NULL;
    new_node->key = strdup(key);
    new_node->value = value ? (Node *)strdup(value) : NULL;
    new_node->next = NULL;
    return new_node;
}

Dictionary* create_dictionary() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict == NULL) return NULL;
    dict->head = NULL;
    return dict;
}

void add_to_dictionary(Dictionary *dict, char *key, char *value) {
    Node *new_node = create_node(key, value);
    if (new_node == NULL) return;
    new_node->next = dict->head;
    dict->head = new_node;
}

Dictionary* convert_lists_to_nested_dict(char **keys, char **values, int length) {
    if (length <= 0) return NULL;
    Dictionary *dict = create_dictionary();
    if (dict == NULL) return NULL;
    for (int i = 0; i < length; ++i) {
        add_to_dictionary(dict, keys[i], values[i]);
    }
    return dict;
}

void print_dictionary(Dictionary *dict, int indent) {
    Node *current = dict->head;
    while (current) {
        for (int i = 0; i < indent; ++i) printf("  ");
        printf("%s: ", current->key);
        if (current->value) {
            printf("%s\n", (char *)current->value);
        } else {
            printf("\n");
            print_dictionary((Dictionary *)current->value, indent + 1);
        }
        current = current->next;
    }
}

void free_dictionary(Dictionary *dict) {
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

int main() {
    char *keys[] = {"a", "b", "c"};
    char *values[] = {"1", "2", "3"};
    int length = sizeof(keys) / sizeof(keys[0]);

    Dictionary *nested_dict = convert_lists_to_nested_dict(keys, values, length);
    if (nested_dict == NULL) return 1;

    print_dictionary(nested_dict, 0);

    free_dictionary(nested_dict);
    return 0;
}