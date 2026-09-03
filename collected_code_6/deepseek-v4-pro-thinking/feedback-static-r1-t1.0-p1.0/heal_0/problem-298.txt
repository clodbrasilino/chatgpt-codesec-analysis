#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    NODE_INT,
    NODE_LIST
} NodeType;

typedef struct NestedListNode {
    NodeType type;
    union {
        int value;
        struct NestedListNode *child;
    } data;
    struct NestedListNode *next;
} NestedListNode;

static NestedListNode *new_int_node(int value) {
    NestedListNode *node = malloc(sizeof(*node));
    if (node != NULL) {
        node->type = NODE_INT;
        node->data.value = value;
        node->next = NULL;
    }
    return node;
}

static NestedListNode *new_list_node(NestedListNode *child) {
    NestedListNode *node = malloc(sizeof(*node));
    if (node != NULL) {
        node->type = NODE_LIST;
        node->data.child = child;
        node->next = NULL;
    }
    return node;
}

static void free_nested_list(NestedListNode *node) {
    while (node != NULL) {
        NestedListNode *next = node->next;
        if (node->type == NODE_LIST) {
            free_nested_list(node->data.child);
        }
        free(node);
        node = next;
    }
}

static bool int_in_flat(int value, const int *flat, size_t flat_len) {
    for (size_t i = 0; i < flat_len; ++i) {
        if (flat[i] == value) {
            return true;
        }
    }
    return false;
}

static bool append_int(int **result, size_t *count, size_t *capacity, int value) {
    if (*count == *capacity) {
        size_t new_capacity;
        if (*capacity == 0) {
            new_capacity = 4;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                free(*result);
                *result = NULL;
                *count = 0;
                *capacity = 0;
                return false;
            }
            new_capacity = *capacity * 2;
        }
        if (new_capacity > SIZE_MAX / sizeof(int)) {
            free(*result);
            *result = NULL;
            *count = 0;
            *capacity = 0;
            return false;
        }
        int *new_result = realloc(*result, new_capacity * sizeof(int));
        if (new_result == NULL) {
            free(*result);
            *result = NULL;
            *count = 0;
            *capacity = 0;
            return false;
        }
        *result = new_result;
        *capacity = new_capacity;
    }
    (*result)[(*count)++] = value;
    return true;
}

static bool collect_matches(const NestedListNode *node, const int *flat, size_t flat_len,
                            int **result, size_t *count, size_t *capacity) {
    for (const NestedListNode *current = node; current != NULL; current = current->next) {
        if (current->type == NODE_INT) {
            if (int_in_flat(current->data.value, flat, flat_len)) {
                if (!append_int(result, count, capacity, current->data.value)) {
                    return false;
                }
            }
        } else if (current->type == NODE_LIST) {
            if (!collect_matches(current->data.child, flat, flat_len, result, count, capacity)) {
                return false;
            }
        }
    }
    return true;
}

bool find_matching_elements(const NestedListNode *nested, const int *flat, size_t flat_len,
                            int **out_matches, size_t *out_count) {
    if (out_matches == NULL || out_count == NULL) {
        return false;
    }
    *out_matches = NULL;
    *out_count = 0;
    if (flat_len > 0 && flat == NULL) {
        return false;
    }
    if (nested == NULL || flat_len == 0) {
        return true;
    }
    int *result = NULL;
    size_t count = 0;
    size_t capacity = 0;
    if (!collect_matches(nested, flat, flat_len, &result, &count, &capacity)) {
        return false;
    }
    *out_matches = result;
    *out_count = count;
    return true;
}

static NestedListNode *create_demo_list(void) {
    NestedListNode *n1 = new_int_node(1);
    if (n1 == NULL) {
        return NULL;
    }
    NestedListNode *n2 = new_int_node(2);
    if (n2 == NULL) {
        free(n1);
        return NULL;
    }
    NestedListNode *n3 = new_int_node(3);
    if (n3 == NULL) {
        free(n1);
        free(n2);
        return NULL;
    }
    NestedListNode *n4 = new_int_node(4);
    if (n4 == NULL) {
        free(n1);
        free(n2);
        free(n3);
        return NULL;
    }
    NestedListNode *sublist = new_list_node(n2);
    if (sublist == NULL) {
        free(n1);
        free(n2);
        free(n3);
        free(n4);
        return NULL;
    }
    n2->next = n3;
    n1->next = sublist;
    sublist->next = n4;
    return n1;
}

int main(void) {
    NestedListNode *nested = create_demo_list();
    if (nested == NULL) {
        return EXIT_FAILURE;
    }
    int flat[] = {2, 4, 6};
    size_t flat_len = sizeof(flat) / sizeof(flat[0]);
    int *matches = NULL;
    size_t match_count = 0;
    if (!find_matching_elements(nested, flat, flat_len, &matches, &match_count)) {
        free_nested_list(nested);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < match_count; ++i) {
        printf("%d\n", matches[i]);
    }
    free(matches);
    free_nested_list(nested);
    return EXIT_SUCCESS;
}