#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictNode {
    char* key;
    int type;
    union {
        char* string_val;
        int int_val;
        struct DictNode* dict_val;
    } value;
    struct DictNode* next;
} DictNode;

typedef struct {
    DictNode* head;
} Dictionary;

int get_dict_depth(Dictionary* dict);

static int get_node_depth(DictNode* node) {
    int max_depth = 0;
    while (node != NULL) {
        if (node->type == 2 && node->value.dict_val != NULL) {
            int depth = get_node_depth(node->value.dict_val);
            if (depth > max_depth) {
                max_depth = depth;
            }
        }
        node = node->next;
    }
    return max_depth + 1;
}

int get_dict_depth(Dictionary* dict) {
    if (dict == NULL || dict->head == NULL) {
        return 0;
    }
    return get_node_depth(dict->head);
}

void free_dict_node(DictNode* node) {
    while (node != NULL) {
        DictNode* next = node->next;
        free(node->key);
        if (node->type == 0) {
            free(node->value.string_val);
        } else if (node->type == 2) {
            free_dict_node(node->value.dict_val);
        }
        free(node);
        node = next;
    }
}

void free_dictionary(Dictionary* dict) {
    if (dict != NULL) {
        free_dict_node(dict->head);
        free(dict);
    }
}

int main(void) {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) return 1;
    
    DictNode* root = (DictNode*)malloc(sizeof(DictNode));
    if (root == NULL) {
        free(dict);
        return 1;
    }
    
    root->key = strdup("a");
    if (root->key == NULL) {
        free(root);
        free(dict);
        return 1;
    }
    root->type = 2;
    root->next = NULL;
    
    DictNode* nested = (DictNode*)malloc(sizeof(DictNode));
    if (nested == NULL) {
        free(root->key);
        free(root);
        free(dict);
        return 1;
    }
    
    nested->key = strdup("b");
    if (nested->key == NULL) {
        free(nested);
        free(root->key);
        free(root);
        free(dict);
        return 1;
    }
    nested->type = 1;
    nested->value.int_val = 42;
    nested->next = NULL;
    nested->value.dict_val = NULL;
    
    root->value.dict_val = nested;
    dict->head = root;
    
    int depth = get_dict_depth(dict);
    printf("Depth: %d\n", depth);
    
    free_dictionary(dict);
    
    return 0;
}