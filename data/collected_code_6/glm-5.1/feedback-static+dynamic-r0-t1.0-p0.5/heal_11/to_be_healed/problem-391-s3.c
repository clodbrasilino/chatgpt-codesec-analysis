#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    const char *key;
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
    free((char *)root->key);
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

Node *lists_to_nested_dict(char * const *lists, const size_t *sizes, size_t num_lists) {
    if (!lists || !sizes || num_lists == 0) return NULL;
    Node *root = create_node("root");
    if (!root) return NULL;
    for (size_t i = 0; i < sizes[0]; i++) {
        if (!lists[0][i]) continue;
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char key[2];
        key[0] = (char)lists[0][i];
        key[1] = '\0';
        Node *current = find_or_create_child(root, key);
        if (!current) { free_tree(root); return NULL; }
        for (size_t j = 1; j < num_lists; j++) {
            if (!lists[j] || i >= sizes[j]) break;
            if (!lists[j][i]) continue;
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char inner_key[3];
            inner_key[0] = (char)lists[j][i];
            inner_key[1] = '\0';
            current = find_or_create_child(current, inner_key);
            if (!current) { free_tree(root); return NULL; }
        }
    }
    return root;
}

void print_tree(const Node *node, int depth) {
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
    const size_t sizes[] = {3, 3, 3};
    Node *dict = lists_to_nested_dict(lists, sizes, 3);
    if (dict) {
        print_tree(dict, 0);
        free_tree(dict);
    }
    return 0;
}