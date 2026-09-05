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

void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->value);
    free_tree(root->next);
    free(root->key);
    free(root);
}

Node *find_or_create_child(Node *parent, const char *key) {
    if (!parent) return NULL;
    Node *curr = parent->value;
    Node *prev = NULL;
    while (curr) {
        if (strcmp(curr->key, key) == 0) return curr;
        prev = curr;
        curr = curr->next;
    }
    Node *new_child = create_node(key);
    if (!new_child) return NULL;
    if (prev) prev->next = new_child;
    else parent->value = new_child;
    return new_child;
}

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
Node *lists_to_nested_dict(char **lists, int *sizes, int num_lists) {
    if (!lists || !sizes || num_lists <= 0) return NULL;
    Node *root = create_node("root");
    if (!root) return NULL;
    for (int i = 0; i < sizes[0]; i++) {
        if (!lists[0][i]) continue;
        Node *current = find_or_create_child(root, &lists[0][i]);
        if (!current) { free_tree(root); return NULL; }
        for (int j = 1; j < num_lists; j++) {
            if (!lists[j] || i >= sizes[j]) break;
            if (!lists[j][i]) continue;
            current = find_or_create_child(current, &lists[j][i]);
            if (!current) { free_tree(root); return NULL; }
        }
    }
    return root;
}

void print_tree(Node *node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%s\n", node->key);
    print_tree(node->value, depth + 1);
    print_tree(node->next, depth);
}

int main() {
    char list1[] = {'A', 'A', 'B'};
    char list2[] = {'X', 'Y', 'X'};
    char list3[] = {'1', '2', '3'};
    char *lists[] = {list1, list2, list3};
    int sizes[] = {3, 3, 3};
    Node *dict = lists_to_nested_dict(lists, sizes, 3);
    if (dict) {
        print_tree(dict, 0);
        free_tree(dict);
    }
    return 0;
}