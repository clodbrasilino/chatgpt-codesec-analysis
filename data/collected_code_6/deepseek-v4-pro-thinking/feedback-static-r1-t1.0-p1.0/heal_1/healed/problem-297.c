#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TYPE_INT,
    TYPE_LIST
} NestedType;

typedef struct NestedList {
    NestedType type;
    union {
        int value;
        struct NestedList *child;
    } data;
    struct NestedList *next;
} NestedList;

static int count_elements(const NestedList *node, size_t *total)
{
    if (!total)
        return -1;

    while (node != NULL) {
        if (node->type == TYPE_INT) {
            (*total)++;
        } else if (node->type == TYPE_LIST) {
            if (count_elements(node->data.child, total) != 0)
                return -1;
        } else {
            return -1;
        }
        node = node->next;
    }

    return 0;
}

static int fill_array(const NestedList *node, int *out, size_t *index)
{
    if (!out || !index)
        return -1;

    while (node != NULL) {
        if (node->type == TYPE_INT) {
            out[*index] = node->data.value;
            (*index)++;
        } else if (node->type == TYPE_LIST) {
            if (fill_array(node->data.child, out, index) != 0)
                return -1;
        } else {
            return -1;
        }
        node = node->next;
    }

    return 0;
}

int *flatten(const NestedList *nested, size_t *out_size)
{
    if (!nested || !out_size)
        return NULL;

    size_t total = 0;
    if (count_elements(nested, &total) != 0)
        return NULL;

    if (total == 0) {
        *out_size = 0;
        return NULL;
    }

    if (total > (size_t)-1 / sizeof(int))
        return NULL;

    int *result = malloc(total * sizeof(int));
    if (!result)
        return NULL;

    size_t index = 0;
    if (fill_array(nested, result, &index) != 0) {
        free(result);
        return NULL;
    }

    *out_size = total;
    return result;
}

int main(void)
{
    NestedList three;
    three.type = TYPE_INT;
    three.data.value = 3;
    three.next = NULL;

    NestedList two;
    two.type = TYPE_INT;
    two.data.value = 2;
    two.next = &three;

    NestedList list1;
    list1.type = TYPE_LIST;
    list1.data.child = &two;
    list1.next = NULL;

    NestedList one;
    one.type = TYPE_INT;
    one.data.value = 1;
    one.next = &list1;

    NestedList root;
    root.type = TYPE_LIST;
    root.data.child = &one;
    root.next = NULL;

    size_t size = (size_t)-1;
    int *flat = flatten(&root, &size);
    if (flat != NULL) {
        for (size_t i = 0; i < size; i++) {
            printf("%d ", flat[i]);
        }
        printf("\n");
        free(flat);
    } else if (size == 0) {
        printf("\n");
    } else {
        fprintf(stderr, "flatten failed\n");
        return 1;
    }

    return 0;
}