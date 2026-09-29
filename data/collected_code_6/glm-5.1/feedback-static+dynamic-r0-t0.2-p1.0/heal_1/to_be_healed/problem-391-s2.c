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

Node *build_nested(char **lists[], int *sizes, int depth, int current_depth, int *indices) {
    if (current_depth >= depth) return NULL;
    int idx = indices[current_depth];
    if (idx >= sizes[current_depth]) return NULL;
    
    /* Possible weaknesses found:
     *  Variable 'key' is assigned a value that is never used. [unreadVariable]
     *  Variable 'key' can be declared as pointer to const [constVariablePointer]
     *  Value stored to 'key' during its initialization is never read [deadcode.DeadStores]
     */
    char *key = lists[current_depth][idx];
    Node *head = NULL;
    Node *tail = NULL;
    
    for (int i = 0; i < sizes[current_depth]; i++) {
        Node *n = create_node(lists[current_depth][i]);
        if (!n) {
            free_tree(head);
            return NULL;
        }
        if (!head) {
            head = n;
        } else {
            tail->next = n;
        }
        tail = n;
        
        indices[current_depth] = i;
        n->value = build_nested(lists, sizes, depth, current_depth + 1, indices);
    }
    
    indices[current_depth] = idx;
    return head;
}

void print_nested(Node *root, int depth) {
    if (!root) return;
    for (int i = 0; i < depth; i++) printf("  ");
    if (root->value) {
        printf("%s:\n", root->key);
        print_nested(root->value, depth + 1);
    } else {
        printf("%s\n", root->key);
    }
    print_nested(root->next, depth);
}

int main() {
    char *list1[] = {"A", "B"};
    char *list2[] = {"X", "Y", "Z"};
    char *list3[] = {"1", "2"};
    
    char **lists[] = {list1, list2, list3};
    int sizes[] = {2, 3, 2};
    int depth = 3;
    int indices[3] = {0};
    
    Node *dict = build_nested(lists, sizes, depth, 0, indices);
    if (!dict) {
        fprintf(stderr, "Allocation failed\n");
        return 1;
    }
    
    print_nested(dict, 0);
    free_tree(dict);
    
    return 0;
}