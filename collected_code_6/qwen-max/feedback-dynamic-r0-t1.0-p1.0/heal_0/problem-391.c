#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char *key;
    struct Node *next;
} Node;

typedef struct Dict {
    char *key;
    void *value;
    struct Dict *parent;
    struct Dict *children;
} Dict;

Dict* dict_new(char *key, void *value) {
    Dict *d = (Dict *)malloc(sizeof(Dict));
    d->key = key;
    d->value = value;
    d->parent = NULL;
    d->children = NULL;
    return d;
}

void dict_insert(Dict *parent, char *key, void *value) {
    if (parent == NULL) return;
    Dict *new_child = dict_new(key, value);
    new_child->parent = parent;
    if (parent->children == NULL) {
        parent->children = new_child;
    } else {
        Dict *current = parent->children;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_child;
    }
}

Dict* lists_to_nested_dict(Node **lists, int list_count) {
    if (list_count <= 0 || lists == NULL) return NULL;
    
    Dict *root = dict_new("root", NULL);
    Dict *current_dict = root;
    
    for (int i = 0; i < list_count; ++i) {
        Node *current_node = lists[i];
        while (current_node != NULL) {
            dict_insert(current_dict, current_node->key, (void *)"value");
            current_dict = current_dict->children;
            current_node = current_node->next;
        }
        while (current_dict && current_dict->parent && current_dict->next == NULL) {
            current_dict = current_dict->parent;
        }
        if (current_dict && current_dict->next) {
            current_dict = current_dict->next;
        }
    }
    
    return root->children;
}

int main() {
    Node *list1 = (Node *)malloc(sizeof(Node));
    list1->key = "a";
    list1->next = (Node *)malloc(sizeof(Node));
    list1->next->key = "b";
    list1->next->next = NULL;

    Node *list2 = (Node *)malloc(sizeof(Node));
    list2->key = "x";
    list2->next = (Node *)malloc(sizeof(Node));
    list2->next->key = "y";
    list2->next->next = (Node *)malloc(sizeof(Node));
    list2->next->next->key = "z";
    list2->next->next->next = NULL;

    Node *list3 = (Node *)malloc(sizeof(Node));
    list3->key = "m";
    list3->next = (Node *)malloc(sizeof(Node));
    list3->next->key = "n";
    list3->next->next = NULL;

    Node *lists[] = {list1, list2, list3};
    Dict *nested_dict = lists_to_nested_dict(lists, 3);

    // Free allocated memory
    while (list1) {
        Node *temp = list1;
        list1 = list1->next;
        free(temp);
    }
    while (list2) {
        Node *temp = list2;
        list2 = list2->next;
        free(temp);
    }
    while (list3) {
        Node *temp = list3;
        list3 = list3->next;
        free(temp);
    }

    // Print nested dictionary and free memory
    while (nested_dict) {
        printf("%s -> ", nested_dict->key);
        Dict *child = nested_dict->children;
        while (child) {
            printf("%s -> ", child->key);
            child = child->next;
        }
        printf("\n");
        child = nested_dict->children;
        while (child) {
            Dict *temp = child;
            child = child->next;
            free(temp);
        }
        nested_dict = nested_dict->next;
    }

    return 0;
}