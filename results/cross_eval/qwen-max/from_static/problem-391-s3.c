#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    void *value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    int size;
} List;

typedef struct Dictionary {
    char *key;
    void *value;
    struct Dictionary *children;
} Dictionary;

List *create_list() {
    return (List *)calloc(1, sizeof(List));
}

Node *create_node(char *key, void *value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = strdup(key);
    node->value = value;
    node->next = NULL;
    return node;
}

void append_to_list(List *list, Node *node) {
    if (list->head == NULL) {
        list->head = node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = (Node *)current->next;
        }
        current->next = (struct Node *)node;
    }
    list->size++;
}

Dictionary *create_dictionary() {
    return (Dictionary *)calloc(1, sizeof(Dictionary));
}

void add_to_dictionary(Dictionary *dict, char *key, void *value) {
    dict->key = strdup(key);
    dict->value = value;
    dict->children = create_dictionary();
}

void convert_lists_to_nested_dict(List *lists[], int num_lists, Dictionary *dict) {
    for (int i = 0; i < num_lists; ++i) {
        Node *current = lists[i]->head;
        Dictionary *current_dict = dict;
        while (current != NULL) {
            if (current_dict->value == NULL) {
                add_to_dictionary(current_dict, current->key, NULL);
            }
            if (strcasecmp(current_dict->key, current->key) == 0) {
                current_dict = (Dictionary *)current_dict->children;
            }
            current = (Node *)current->next;
        }
    }
}

void free_node(Node *node) {
    if (node) {
        free(node->key);
        free(node);
    }
}

void free_list(List *list) {
    if (list) {
        Node *current = list->head;
        Node *next = NULL;
        while (current != NULL) {
            next = (Node *)current->next;
            free_node(current);
            current = next;
        }
        free(list);
    }
}

void free_dictionary(Dictionary *dict) {
    if (dict) {
        free_dictionary((Dictionary *)dict->children);
        free(dict->key);
        free(dict);
    }
}

int main() {
    List *list1 = create_list();
    List *list2 = create_list();
    List *list3 = create_list();

    append_to_list(list1, create_node("a", NULL));
    append_to_list(list1, create_node("b", NULL));
    append_to_list(list1, create_node("c", NULL));

    append_to_list(list2, create_node("d", NULL));
    append_to_list(list2, create_node("e", NULL));

    append_to_list(list3, create_node("f", NULL));
    append_to_list(list3, create_node("g", NULL));

    List *lists[] = {list1, list2, list3};
    Dictionary *root_dict = create_dictionary();
    convert_lists_to_nested_dict(lists, 3, root_dict);

    free_list(list1);
    free_list(list2);
    free_list(list3);
    free_dictionary(root_dict);
    return 0;
}