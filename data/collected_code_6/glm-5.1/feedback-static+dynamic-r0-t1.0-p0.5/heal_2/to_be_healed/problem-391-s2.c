#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    struct Node *value;
    struct Node *next;
} Node;

Node *create_node(const char *key) {
    Node *n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->key = strdup(key);
    if (!n->key) { free(n); return NULL; }
    n->value = NULL;
    n->next = NULL;
    return n;
}

void free_node(Node *n) {
    if (!n) return;
    free(n->key);
    free_node(n->value);
    free_node(n->next);
    free(n);
}

Node *find_or_create(Node *parent, const char *key) {
    if (!parent) return NULL;
    Node *curr = parent->value;
    Node *prev = NULL;
    while (curr) {
        if (strcmp(curr->key, key) == 0) return curr;
        prev = curr;
        curr = curr->next;
    }
    Node *new_node = create_node(key);
    if (!new_node) return NULL;
    if (prev) prev->next = new_node;
    else parent->value = new_node;
    return new_node;
}

Node *lists_to_nested_dict(char ***lists, const int *sizes, int count) {
    if (!lists || count <= 0) return NULL;
    Node *root = create_node("root");
    if (!root) return NULL;
    for (int i = 0; i < sizes[0]; i++) {
        Node *current = find_or_create(root, lists[0][i]);
        if (!current) { free_node(root); return NULL; }
        for (int j = 1; j < count; j++) {
            if (i < sizes[j]) {
                current = find_or_create(current, lists[j][i]);
                if (!current) { free_node(root); return NULL; }
            }
        }
    }
    return root;
}

void print_dict(Node *n, int depth) {
    if (!n) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%s\n", n->key);
    print_dict(n->value, depth + 1);
    print_dict(n->next, depth);
}

int main(void) {
    char *list1[] = {"A", "B", "C"};
    char *list2[] = {"X", "Y", "Z"};
    char *list3[] = {"1", "2", "3"};
    char **lists[] = {list1, list2, list3};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    int sizes[] = {3, 3, 3};
    Node *dict = lists_to_nested_dict(lists, sizes, 3);
    if (dict) {
        print_dict(dict->value, 0);
        free_node(dict);
    }
    return 0;
}