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

    int *result = malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    size_t valid_count = 0;
    List *current_list = lists;

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         *  Assuming that condition 'current_list!=NULL' is not redundant
         */
        if (current_list != NULL && current_list->head != NULL) {
            result[valid_count++] = current_list->head->data;
        }
        /* Possible weaknesses found:
         *  Null pointer dereference
         *  Either the condition 'current_list!=NULL' is redundant or there is possible null pointer dereference: current_list. [nullPointerRedundantCheck]
         */
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
    Node n4 = {4, NULL};

    List l3 = {&n3, NULL};
    List l2 = {&n1, &l3};
    List l1 = {&n4, &l2};

    size_t out_count = 0;
    int *elements = get_first_elements(&l1, 3, &out_count);

    if (elements != NULL) {
        for (size_t i = 0; i < out_count; ++i) {
            printf("%d\n", elements[i]);
        }
        free(elements);
    }

    return 0;
}