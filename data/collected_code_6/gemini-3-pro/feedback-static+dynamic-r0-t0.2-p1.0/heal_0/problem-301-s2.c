#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictionaryNode {
    char *key;
    struct DictionaryNode *value_dict;
    struct DictionaryNode *next;
} DictionaryNode;

DictionaryNode* create_node(const char *key) {
    if (!key) return NULL;
    DictionaryNode *node = (DictionaryNode*)malloc(sizeof(DictionaryNode));
    if (!node) return NULL;
    node->key = strdup(key);
    if (!node->key) {
        free(node);
        return NULL;
    }
    node->value_dict = NULL;
    node->next = NULL;
    return node;
}

void free_dictionary(DictionaryNode *head) {
    DictionaryNode *current = head;
    while (current != NULL) {
        DictionaryNode *next = current->next;
        if (current->key) {
            free(current->key);
        }
        if (current->value_dict) {
            free_dictionary(current->value_dict);
        }
        free(current);
        current = next;
    }
}

int get_dictionary_depth(DictionaryNode *head) {
    if (head == NULL) {
        return 0;
    }

    int max_depth = 0;
    DictionaryNode *current = head;

    while (current != NULL) {
        int depth = 1;
        if (current->value_dict != NULL) {
            depth += get_dictionary_depth(current->value_dict);
        }
        if (depth > max_depth) {
            max_depth = depth;
        }
        current = current->next;
    }

    return max_depth;
}

int main() {
    DictionaryNode *root = create_node("root1");
    if (!root) return 1;

    root->next = create_node("root2");
    if (!root->next) {
        free_dictionary(root);
        return 1;
    }

    root->value_dict = create_node("child1");
    if (!root->value_dict) {
        free_dictionary(root);
        return 1;
    }

    root->value_dict->value_dict = create_node("grandchild1");
    if (!root->value_dict->value_dict) {
        free_dictionary(root);
        return 1;
    }

    int depth = get_dictionary_depth(root);
    printf("Dictionary depth: %d\n", depth);

    free_dictionary(root);

    return 0;
}