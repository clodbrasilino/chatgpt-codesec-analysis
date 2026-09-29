#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    INT_TYPE,
    STRING_TYPE,
    DICT_TYPE
} NodeType;

typedef struct Node {
    char *key;
    NodeType type;
    union {
        int int_val;
        char *string_val;
        struct Node *dict_val;
    } value;
    struct Node *next;
} Node;

static char *clone_string(const char *src) {
    size_t max_len = 1048576;
    const char *end = memchr(src, '\0', max_len);
    if (end == NULL) return NULL;
    size_t len = end - src + 1;
    char *dest = (char *)malloc(len);
    if (dest == NULL) return NULL;
    snprintf(dest, len, "%s", src);
    return dest;
}

static Node *create_int_node(const char *key, int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->key = clone_string(key);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }
    node->type = INT_TYPE;
    node->value.int_val = val;
    node->next = NULL;
    return node;
}

static Node *create_string_node(const char *key, const char *val) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->key = clone_string(key);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }
    node->value.string_val = clone_string(val);
    if (node->value.string_val == NULL) {
        free(node->key);
        free(node);
        return NULL;
    }
    node->type = STRING_TYPE;
    node->next = NULL;
    return node;
}

static Node *create_dict_node(const char *key, Node *val) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->key = clone_string(key);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }
    node->type = DICT_TYPE;
    node->value.dict_val = val;
    node->next = NULL;
    return node;
}

static void free_dict(Node *dict) {
    Node *curr = dict;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr->key);
        if (curr->type == STRING_TYPE) {
            free(curr->value.string_val);
        } else if (curr->type == DICT_TYPE) {
            free_dict(curr->value.dict_val);
        }
        free(curr);
        curr = next;
    }
}

int find_depth(Node *dict) {
    if (dict == NULL) {
        return 0;
    }
    int max_child_depth = 0;
    Node *curr = dict;
    while (curr != NULL) {
        if (curr->type == DICT_TYPE) {
            int current_depth = find_depth(curr->value.dict_val);
            if (current_depth > max_child_depth) {
                max_child_depth = current_depth;
            }
        }
        curr = curr->next;
    }
    return 1 + max_child_depth;
}

int main(void) {
    Node *inner_dict = create_int_node("inner_key", 42);
    if (inner_dict == NULL) return EXIT_FAILURE;
    
    Node *middle_dict = create_dict_node("middle_dict", inner_dict);
    if (middle_dict == NULL) {
        free_dict(inner_dict);
        return EXIT_FAILURE;
    }
    
    Node *root_dict = create_string_node("root_key", "value");
    if (root_dict == NULL) {
        free_dict(middle_dict);
        return EXIT_FAILURE;
    }
    
    Node *nested_node = create_dict_node("nested", middle_dict);
    if (nested_node == NULL) {
        free_dict(root_dict);
        free_dict(middle_dict);
        return EXIT_FAILURE;
    }
    
    root_dict->next = nested_node;

    int depth = find_depth(root_dict);
    printf("Depth: %d\n", depth);

    free_dict(root_dict);
    return EXIT_SUCCESS;
}