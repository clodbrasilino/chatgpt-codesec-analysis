#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    /* Possible weaknesses found:
     *  struct member 'Node::next' is never used. [unusedStructMember]
     */
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *next;
} List;

int *get_first_elements(List *lists, size_t count, size_t *out_count) {
    if (lists == NULL || out_count == NULL) {
        return NULL;
    }

    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    size_t valid_count = 0;
    List *current_list = lists;

    for (size_t i = 0; i < count; ++i) {
        if (current_list == NULL) {
            break;
        }

        if (current_list->head != NULL) {
            result[valid_count++] = current_list->head->data;
        }

        current_list = current_list->next;
    }

    *out_count = valid_count;
    return result;
}

int main(void) {
    Node n1 = {1, NULL};
    /* Possible weaknesses found:
     *  Variable 'n2' is assigned a value that is never used. [unreadVariable]
     */
    Node n2 = {2, NULL};
    Node n3 = {3, NULL};
    /* Possible weaknesses found:
     *  Variable 'n4' is assigned a value that is never used. [unreadVariable]
     */
    Node n4 = {4, NULL};

    List l1 = {&n1, NULL};
    List l2 = {&n3, NULL};
    List l3 = {NULL, NULL};

    l1.next = &l2;
    l2.next = &l3;

    size_t list_count = 3;
    size_t out_count = 0;

    int *firsts = get_first_elements(&l1, list_count, &out_count);

    if (firsts != NULL) {
        for (size_t i = 0; i < out_count; ++i) {
            printf("%d\n", firsts[i]);
        }
        free(firsts);
    }

    return 0;
}