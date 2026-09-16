#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct NestedNode NestedNode;
typedef struct NestedList NestedList;
typedef struct IntList IntList;

struct NestedList {
    NestedNode **items;
    size_t length;
    size_t capacity;
};

struct NestedNode {
    int is_list;
    union {
        int value;
        NestedList *list;
    } data;
};

struct IntList {
    int *items;
    size_t length;
    size_t capacity;
};

static NestedList *nested_list_create(void);
static int nested_list_add_item(NestedList *list, NestedNode *node);
static NestedNode *nested_node_create_int(int value);
static NestedNode *nested_node_create_list(NestedList *list);
static void nested_node_free(NestedNode *node);
static void nested_list_free(NestedList *list);
static IntList *int_list_create(void);
static int int_list_add(IntList *list, int value);
static void int_list_free(IntList *list);
static int flatten_recursive(const NestedNode *node, IntList *out);
static IntList *flatten(const NestedList *list);
static int nested_list_add_int(NestedList *list, int value);
static int nested_list_add_list(NestedList *list, NestedList *inner);

static NestedList *nested_list_create(void) {
    NestedList *list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }
    list->items = NULL;
    list->length = 0;
    list->capacity = 0;
    return list;
}

static int nested_list_add_item(NestedList *list, NestedNode *node) {
    if (list == NULL || node == NULL) {
        return -1;
    }
    if (list->length == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        NestedNode **new_items = realloc(list->items, new_capacity * sizeof(*new_items));
        if (new_items == NULL) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->length++] = node;
    return 0;
}

static NestedNode *nested_node_create_int(int value) {
    NestedNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->is_list = 0;
    node->data.value = value;
    return node;
}

static NestedNode *nested_node_create_list(NestedList *list) {
    if (list == NULL) {
        return NULL;
    }
    NestedNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->is_list = 1;
    node->data.list = list;
    return node;
}

static void nested_node_free(NestedNode *node) {
    if (node == NULL) {
        return;
    }
    if (node->is_list) {
        nested_list_free(node->data.list);
    }
    free(node);
}

static void nested_list_free(NestedList *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->length; i++) {
        nested_node_free(list->items[i]);
    }
    free(list->items);
    free(list);
}

static IntList *int_list_create(void) {
    IntList *list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }
    list->items = NULL;
    list->length = 0;
    list->capacity = 0;
    return list;
}

static int int_list_add(IntList *list, int value) {
    if (list == NULL) {
        return -1;
    }
    if (list->length == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        int *new_items = realloc(list->items, new_capacity * sizeof(*new_items));
        if (new_items == NULL) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->length++] = value;
    return 0;
}

static void int_list_free(IntList *list) {
    if (list == NULL) {
        return;
    }
    free(list->items);
    free(list);
}

static int flatten_recursive(const NestedNode *node, IntList *out) {
    if (node == NULL || out == NULL) {
        return -1;
    }
    if (!node->is_list) {
        return int_list_add(out, node->data.value);
    }
    const NestedList *list = node->data.list;
    if (list == NULL) {
        return -1;
    }
    for (size_t i = 0; i < list->length; i++) {
        if (flatten_recursive(list->items[i], out) != 0) {
            return -1;
        }
    }
    return 0;
}

static IntList *flatten(const NestedList *list) {
    if (list == NULL) {
        return NULL;
    }
    IntList *out = int_list_create();
    if (out == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < list->length; i++) {
        if (flatten_recursive(list->items[i], out) != 0) {
            int_list_free(out);
            return NULL;
        }
    }
    return out;
}

static int nested_list_add_int(NestedList *list, int value) {
    if (list == NULL) {
        return -1;
    }
    NestedNode *node = nested_node_create_int(value);
    if (node == NULL) {
        return -1;
    }
    if (nested_list_add_item(list, node) != 0) {
        nested_node_free(node);
        return -1;
    }
    return 0;
}

static int nested_list_add_list(NestedList *list, NestedList *inner) {
    if (list == NULL || inner == NULL) {
        return -1;
    }
    NestedNode *node = nested_node_create_list(inner);
    if (node == NULL) {
        nested_list_free(inner);
        return -1;
    }
    if (nested_list_add_item(list, node) != 0) {
        nested_node_free(node);
        return -1;
    }
    return 0;
}

int main(void) {
    NestedList *root = nested_list_create();
    if (root == NULL) {
        return EXIT_FAILURE;
    }

    if (nested_list_add_int(root, 1) != 0) {
        goto error;
    }

    NestedList *inner1 = nested_list_create();
    if (inner1 == NULL) {
        goto error;
    }
    if (nested_list_add_int(inner1, 2) != 0) {
        nested_list_free(inner1);
        goto error;
    }
    if (nested_list_add_int(inner1, 3) != 0) {
        nested_list_free(inner1);
        goto error;
    }
    if (nested_list_add_list(root, inner1) != 0) {
        goto error;
    }

    NestedList *inner2 = nested_list_create();
    if (inner2 == NULL) {
        goto error;
    }
    if (nested_list_add_int(inner2, 4) != 0) {
        nested_list_free(inner2);
        goto error;
    }

    NestedList *inner3 = nested_list_create();
    if (inner3 == NULL) {
        nested_list_free(inner2);
        goto error;
    }
    if (nested_list_add_int(inner3, 5) != 0) {
        nested_list_free(inner3);
        nested_list_free(inner2);
        goto error;
    }
    if (nested_list_add_list(inner2, inner3) != 0) {
        nested_list_free(inner2);
        goto error;
    }
    if (nested_list_add_list(root, inner2) != 0) {
        goto error;
    }

    if (nested_list_add_int(root, 6) != 0) {
        goto error;
    }

    IntList *flat = flatten(root);
    if (flat == NULL) {
        goto error;
    }

    for (size_t i = 0; i < flat->length; i++) {
        printf("%d\n", flat->items[i]);
    }

    int_list_free(flat);
    nested_list_free(root);
    return EXIT_SUCCESS;

error:
    nested_list_free(root);
    return EXIT_FAILURE;
}