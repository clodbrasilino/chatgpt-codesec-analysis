#include <stdio.h>
#include <stdlib.h>

typedef struct DictionaryNode {
    struct DictionaryNode** children;
    size_t num_children;
} DictionaryNode;

int find_dictionary_depth(DictionaryNode* root) {
    if (root == NULL) {
        return 0;
    }

    int max_depth = 0;
    for (size_t i = 0; i < root->num_children; ++i) {
        int child_depth = find_dictionary_depth(root->children[i]);
        if (child_depth > max_depth) {
            max_depth = child_depth;
        }
    }

    return max_depth + 1;
}

DictionaryNode* create_node(size_t num_children) {
    DictionaryNode* node = (DictionaryNode*)malloc(sizeof(DictionaryNode));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }

    node->num_children = num_children;
    if (num_children > 0) {
        node->children = (DictionaryNode**)malloc(num_children * sizeof(DictionaryNode*));
        if (node->children == NULL) {
            free(node);
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < num_children; ++i) {
            node->children[i] = NULL;
        }
    } else {
        node->children = NULL;
    }

    return node;
}

void free_dictionary(DictionaryNode* root) {
    if (root == NULL) {
        return;
    }

    for (size_t i = 0; i < root->num_children; ++i) {
        free_dictionary(root->children[i]);
    }

    free(root->children);
    free(root);
}

int main(void) {
    DictionaryNode* root = create_node(2);
    
    root->children[0] = create_node(1);
    root->children[0]->children[0] = create_node(0);
    
    root->children[1] = create_node(2);
    root->children[1]->children[0] = create_node(0);
    root->children[1]->children[1] = create_node(1);
    root->children[1]->children[1]->children[0] = create_node(0);

    int depth = find_dictionary_depth(root);
    printf("Dictionary depth: %d\n", depth);

    free_dictionary(root);

    return 0;
}