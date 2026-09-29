#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictionaryNode {
    char *key;
    struct DictionaryNode *value_dict;
    struct DictionaryNode *next;
} DictionaryNode;

DictionaryNode* create_node(const char *key, DictionaryNode *value_dict) {
    if (!key) return NULL;
    
    DictionaryNode *node = (DictionaryNode *)malloc(sizeof(DictionaryNode));
    if (!node) return NULL;
    
    node->key = strdup(key);
    if (!node->key) {
        free(node);
        return NULL;
    }
    
    node->value_dict = value_dict;
    node->next = NULL;
    
    return node;
}

void free_dictionary(DictionaryNode *head) {
    DictionaryNode *current = head;
    while (current != NULL) {
        DictionaryNode *next = current->next;
        free(current->key);
        if (current->value_dict != NULL) {
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
        int current_depth = 1;
        if (current->value_dict != NULL) {
            current_depth += get_dictionary_depth(current->value_dict);
        }
        
        if (current_depth > max_depth) {
            max_depth = current_depth;
        }
        
        current = current->next;
    }
    
    return max_depth;
}

int main(void) {
    DictionaryNode *inner_dict2 = create_node("key3", NULL);
    if (!inner_dict2) return 1;

    DictionaryNode *inner_dict1 = create_node("key2", inner_dict2);
    if (!inner_dict1) {
        free_dictionary(inner_dict2);
        return 1;
    }

    DictionaryNode *root_dict = create_node("key1", inner_dict1);
    if (!root_dict) {
        free_dictionary(inner_dict1);
        return 1;
    }

    DictionaryNode *sibling_node = create_node("key4", NULL);
    if (!sibling_node) {
        free_dictionary(root_dict);
        return 1;
    }
    root_dict->next = sibling_node;

    int depth = get_dictionary_depth(root_dict);
    printf("Dictionary depth: %d\n", depth);

    free_dictionary(root_dict);

    return 0;
}