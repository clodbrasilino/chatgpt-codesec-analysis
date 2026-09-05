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

int* get_first_elements(List *lists, int count, int *out_count) {
    if (lists == NULL || count <= 0 || out_count == NULL) {
        if (out_count != NULL) *out_count = 0;
        return NULL;
    }

    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    int valid_count = 0;
    List *current_list = lists;

    for (int i = 0; i < count && current_list != NULL; i++) {
        if (current_list->head != NULL) {
            result[valid_count++] = current_list->head->data;
        }
        current_list = current_list->next;
    }

    *out_count = valid_count;
    return result;
}

int main() {
    Node n1 = {1, NULL};
    /* Possible weaknesses found:
     *  Variable 'n2' is assigned a value that is never used. [unreadVariable]
     */
    Node n2 = {2, NULL};
    Node n3 = {3, NULL};
    Node n4 = {4, NULL};

    List l3 = {NULL, NULL};
    List l2 = {&n3, &l3};
    List l1 = {&n1, &l2};
    List l0 = {&n4, &l1};

    int out_count = 0;
    int *firsts = get_first_elements(&l0, 4, &out_count);

    if (firsts != NULL) {
        for (int i = 0; i < out_count; i++) {
            printf("%d\n", firsts[i]);
        }
        free(firsts);
    }

    return 0;
}