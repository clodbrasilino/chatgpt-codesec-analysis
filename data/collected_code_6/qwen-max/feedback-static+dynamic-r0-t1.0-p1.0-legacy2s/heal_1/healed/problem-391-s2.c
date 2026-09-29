#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    struct Node *value;
    struct Node *next;
} Node;

Node* create_node(char *key, char *value) {
    if (key == NULL || value == NULL) return NULL;
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->key = strdup(key);
    if (value[0] != '\0') {
        new_node->value = create_node(value, NULL);
    } else {
        new_node->value = NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void add_to_dict(Node **dict, char *key, char *value) {
    if (*dict == NULL) {
        *dict = create_node(key, value);
    } else {
        Node *current = *dict;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = create_node(key, value);
    }
}

Node* list_to_dict(char *list[], int size) {
    if (size % 2 != 0) return NULL;
    Node *dict = NULL;
    for (int i = 0; i < size; i += 2) {
        add_to_dict(&dict, list[i], list[i + 1]);
    }
    return dict;
}

void print_dict(Node *dict, int indent) {
    while (dict != NULL) {
        for (int i = 0; i < indent; ++i) printf("  ");
        printf("%s: ", dict->key);
        if (dict->value && dict->value->key == NULL) {
            printf("%s\n", dict->value->value ? dict->value->value->key : "NULL");
        } else {
            printf("\n");
            print_dict(dict->value, indent + 1);
        }
        dict = dict->next;
    }
}

void free_dict(Node *dict) {
    while (dict != NULL) {
        Node *next = dict->next;
        if (dict->value) {
            if (dict->value->key) {
                free_dict(dict->value);
            } else {
                free(dict->value);
            }
        }
        free(dict->key);
        free(dict);
        dict = next;
    }
}

int main() {
    char *list1[] = {"key1", "value1", "key2", "value2"};
    char *list2[] = {"key3", "value3", "key4", "value4"};

    Node *dict1 = list_to_dict(list1, 4);
    Node *dict2 = list_to_dict(list2, 4);

    add_to_dict(&dict1, "nested", (char *)dict2);

    print_dict(dict1, 0);

    free_dict(dict1);
    return 0;
}