#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct NestedListNode {
    int is_list;
    int value;
    struct NestedListNode *list;
    struct NestedListNode *next;
} NestedListNode;

typedef struct {
    int *items;
    size_t size;
    size_t capacity;
} IntArray;

static int append_to_array(IntArray *arr, int value) {
    if (arr->size == arr->capacity) {
        if (arr->capacity > ((size_t)-1) / sizeof(int) / 2) {
            return -1;
        }
        size_t new_capacity = arr->capacity == 0 ? 4 : arr->capacity * 2;
        int *new_items = realloc(arr->items, new_capacity * sizeof(*new_items));
        if (new_items == NULL) {
            return -1;
        }
        arr->items = new_items;
        arr->capacity = new_capacity;
    }
    arr->items[arr->size] = value;
    arr->size++;
    return 0;
}

static int find_in_nested(const NestedListNode *node, const int *list, size_t list_size, IntArray *result) {
    while (node != NULL) {
        if (node->is_list) {
            if (find_in_nested(node->list, list, list_size, result) != 0) {
                return -1;
            }
        } else {
            for (size_t i = 0; i < list_size; i++) {
                if (list[i] == node->value) {
                    if (append_to_array(result, node->value) != 0) {
                        return -1;
                    }
                    break;
                }
            }
        }
        node = node->next;
    }
    return 0;
}

int *find_common_elements(const NestedListNode *nested, const int *list, size_t list_size, size_t *result_size) {
    if (result_size == NULL) {
        return NULL;
    }
    *result_size = 0;
    if (list == NULL && list_size > 0) {
        return NULL;
    }
    IntArray result = {0};
    if (find_in_nested(nested, list, list_size, &result) != 0) {
        free(result.items);
        return NULL;
    }
    *result_size = result.size;
    return result.items;
}

int main(void) {
    NestedListNode n1 = {0, 1, NULL, NULL};
    NestedListNode n2 = {0, 2, NULL, NULL};
    NestedListNode n3 = {0, 3, NULL, NULL};
    NestedListNode n4 = {0, 4, NULL, NULL};
    NestedListNode n5 = {0, 5, NULL, NULL};
    NestedListNode n6 = {0, 6, NULL, NULL};
    NestedListNode n7 = {0, 7, NULL, NULL};
    NestedListNode list_5_6 = {1, 0, NULL, NULL};
    NestedListNode list_4_5_6 = {1, 0, NULL, NULL};
    NestedListNode list_2_3 = {1, 0, NULL, NULL};

    n5.next = &n6;
    list_5_6.list = &n5;
    list_4_5_6.list = &n4;
    n4.next = &list_5_6;
    list_2_3.list = &n2;
    n2.next = &n3;
    n1.next = &list_2_3;
    list_2_3.next = &list_4_5_6;
    list_4_5_6.next = &n7;

    int list[] = {2, 5, 7, 9};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t result_size = 0;
    int *result = find_common_elements(&n1, list, list_size, &result_size);

    for (size_t i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}