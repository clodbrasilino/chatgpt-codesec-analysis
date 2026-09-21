#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

typedef enum {
    VALUE_INT,
    VALUE_STRING,
    VALUE_DICT
} ValueType;

typedef struct DictNode DictNode;

typedef struct {
    ValueType type;
    union {
        int int_val;
        char *string_val;
        DictNode *dict_val;
    } data;
} DictValue;

struct DictNode {
    char *key;
    DictValue value;
    DictNode *next;
};

char* duplicate_string(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    const char *ptr = str;
    
    while (len < MAX_STR_LEN && *ptr != '\0') {
        len++;
        ptr++;
    }

    char *copy = (char*)malloc(len + 1);
    if (copy != NULL) {
        size_t i;
        for (i = 0; i < len; i++) {
            copy[i] = str[i];
        }
        copy[len] = '\0';
    }
    
    return copy;
}

size_t get_dict_depth(const DictNode *dict) {
    if (dict == NULL) {
        return 0;
    }

    size_t max_depth = 0;
    const DictNode *current = dict;

    while (current != NULL) {
        if (current->value.type == VALUE_DICT) {
            size_t child_depth = get_dict_depth(current->value.data.dict_val);
            if (child_depth > max_depth) {
                max_depth = child_depth;
            }
        }
        current = current->next;
    }

    return max_depth + 1;
}

DictNode* create_node(const char *key, ValueType type) {
    if (key == NULL) {
        return NULL;
    }

    DictNode *node = (DictNode*)malloc(sizeof(DictNode));
    if (node == NULL) {
        return NULL;
    }

    node->key = duplicate_string(key);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }

    node->value.type = type;
    node->next = NULL;
    
    if (type == VALUE_INT) {
        node->value.data.int_val = 0;
    } else if (type == VALUE_STRING) {
        node->value.data.string_val = NULL;
    } else if (type == VALUE_DICT) {
        node->value.data.dict_val = NULL;
    }

    return node;
}

void free_dict(DictNode *dict) {
    DictNode *current = dict;
    while (current != NULL) {
        DictNode *next = current->next;
        
        if (current->key != NULL) {
            free(current->key);
        }
        
        if (current->value.type == VALUE_STRING && current->value.data.string_val != NULL) {
            free(current->value.data.string_val);
        } else if (current->value.type == VALUE_DICT && current->value.data.dict_val != NULL) {
            free_dict(current->value.data.dict_val);
        }
        
        free(current);
        current = next;
    }
}

int main(void) {
    DictNode *root = create_node("level_1", VALUE_DICT);
    if (root == NULL) {
        return EXIT_FAILURE;
    }

    DictNode *child1 = create_node("level_2", VALUE_DICT);
    if (child1 == NULL) {
        free_dict(root);
        return EXIT_FAILURE;
    }
    root->value.data.dict_val = child1;

    DictNode *child2 = create_node("level_3", VALUE_INT);
    if (child2 == NULL) {
        free_dict(root);
        return EXIT_FAILURE;
    }
    child2->value.data.int_val = 100;
    child1->value.data.dict_val = child2;

    DictNode *sibling = create_node("level_1_sibling", VALUE_STRING);
    if (sibling == NULL) {
        free_dict(root);
        return EXIT_FAILURE;
    }
    
    sibling->value.data.string_val = duplicate_string("hello");
    if (sibling->value.data.string_val == NULL) {
        free_dict(sibling);
        free_dict(root);
        return EXIT_FAILURE;
    }
    
    root->next = sibling;

    size_t depth = get_dict_depth(root);
    printf("%zu\n", depth);

    free_dict(root);

    return EXIT_SUCCESS;
}