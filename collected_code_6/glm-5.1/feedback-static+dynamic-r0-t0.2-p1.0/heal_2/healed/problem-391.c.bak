#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dict {
    char *key;
    struct Dict *child;
    struct Dict *next;
} Dict;

Dict *create_node(const char *key) {
    Dict *node = malloc(sizeof(Dict));
    if (!node) return NULL;
    node->key = malloc(strlen(key) + 1);
    if (!node->key) {
        free(node);
        return NULL;
    }
    strcpy(node->key, key);
    node->child = NULL;
    node->next = NULL;
    return node;
}

Dict *find_or_create_child(Dict *parent, const char *key) {
    if (!parent) return NULL;
    Dict *curr = parent->child;
    Dict *prev = NULL;
    while (curr) {
        if (strcmp(curr->key, key) == 0) return curr;
        prev = curr;
        curr = curr->next;
    }
    Dict *new_node = create_node(key);
    if (!new_node) return NULL;
    if (prev) {
        prev->next = new_node;
    } else {
        parent->child = new_node;
    }
    return new_node;
}

Dict *lists_to_nested_dict(char **lists, const int *sizes, int num_lists) {
    if (!lists || !sizes || num_lists <= 0) return NULL;
    Dict *root = create_node("root");
    if (!root) return NULL;
    for (int i = 0; i < sizes[0]; i++) {
        if (!lists[0][i]) continue;
        const char key[2] = {lists[0][i], '\0'};
        Dict *level = find_or_create_child(root, key);
        if (!level) continue;
        for (int j = 1; j < num_lists; j++) {
            if (sizes[j] <= i) break;
            if (!lists[j][i]) continue;
            const char nested_key[2] = {lists[j][i], '\0'};
            level = find_or_create_child(level, nested_key);
            if (!level) break;
        }
    }
    return root;
}

void print_dict(Dict *dict, int depth) {
    if (!dict) return;
    Dict *curr = dict;
    while (curr) {
        for (int i = 0; i < depth; i++) printf("  ");
        printf("%s\n", curr->key);
        print_dict(curr->child, depth + 1);
        curr = curr->next;
    }
}

void free_dict(Dict *dict) {
    if (!dict) return;
    free_dict(dict->child);
    free_dict(dict->next);
    free(dict->key);
    free(dict);
}

int main() {
    char list1[] = {'A', 'A', 'B'};
    char list2[] = {'X', 'Y', 'X'};
    char list3[] = {'1', '2', '3'};
    char *lists[] = {list1, list2, list3};
    const int sizes[] = {3, 3, 3};
    int num_lists = 3;
    Dict *root = lists_to_nested_dict(lists, sizes, num_lists);
    if (root) {
        print_dict(root->child, 0);
        free_dict(root);
    }
    return 0;
}