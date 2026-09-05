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
        if (out_count != NULL) {
            *out_count = 0;
        }
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

    if (valid_count == 0) {
        free(result);
        *out_count = 0;
        return NULL;
    }

    if (valid_count < count) {
        int *shrunk_result = (int *)realloc(result, valid_count * sizeof(int));
        if (shrunk_result != NULL) {
            result = shrunk_result;
        }
    }

    *out_count = valid_count;
    return result;
}

int main() {
    Node n1 = {1, NULL};
    Node n2 = {2, NULL};
    Node n3 = {3, NULL};

    List l1 = {&n1, NULL};
    List l2 = {&n2, NULL};
    List l3 = {&n3, NULL};

    l1.next = &l2;
    l2.next = &l3;

    int out_count = 0;
    int *firsts = get_first_elements(&l1, 3, &out_count);

    if (firsts != NULL) {
        for (int i = 0; i < out_count; i++) {
            printf("%d\n", firsts[i]);
        }
        free(firsts);
    }

    return 0;
}