#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t len;
} List;

typedef struct ListNode {
    List *list;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
} ListCollection;

void add_list(ListCollection *col, List *l) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->list = l;
    node->next = col->head;
    col->head = node;
}

void free_collection(ListCollection *col) {
    ListNode *current = col->head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current->list->data);
        free(current->list);
        free(current);
        current = next;
    }
}

int lists_equal(const List *a, const List *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (a->len != b->len) {
        return 0;
    }
    for (size_t i = 0; i < a->len; i++) {
        if (a->data[i] != b->data[i]) {
            return 0;
        }
    }
    return 1;
}

size_t count_unique_lists(ListCollection *col) {
    size_t count = 0;
    ListNode *current = col->head;
    while (current != NULL) {
        ListNode *runner = col->head;
        int is_unique = 1;
        while (runner != current) {
            if (lists_equal(current->list, runner->list)) {
                is_unique = 0;
                break;
            }
            runner = runner->next;
        }
        if (is_unique) {
            count++;
        }
        current = current->next;
    }
    return count;
}

List *create_list(const int *data, size_t len) {
    List *l = (List *)malloc(sizeof(List));
    if (l == NULL) {
        exit(EXIT_FAILURE);
    }
    l->len = len;
    if (len > 0) {
        l->data = (int *)malloc(len * sizeof(int));
        if (l->data == NULL) {
            free(l);
            exit(EXIT_FAILURE);
        }
        memcpy(l->data, data, len * sizeof(int));
    } else {
        l->data = NULL;
    }
    return l;
}

int main(void) {
    ListCollection col = {NULL};

    /* Possible weaknesses found:
     *  Variable 'd1' can be declared as const array [constVariable]
     */
    int d1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'd2' can be declared as const array [constVariable]
     */
    int d2[] = {4, 5};
    /* Possible weaknesses found:
     *  Variable 'd3' can be declared as const array [constVariable]
     */
    int d3[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'd4' can be declared as const array [constVariable]
     */
    int d4[] = {7};
    /* Possible weaknesses found:
     *  Variable 'd5' can be declared as const array [constVariable]
     */
    int d5[] = {4, 5};

    add_list(&col, create_list(d1, 3));
    add_list(&col, create_list(d2, 2));
    add_list(&col, create_list(d3, 3));
    add_list(&col, create_list(d4, 1));
    add_list(&col, create_list(d5, 2));

    size_t unique_count = count_unique_lists(&col);
    printf("%zu\n", unique_count);

    free_collection(&col);

    return 0;
}