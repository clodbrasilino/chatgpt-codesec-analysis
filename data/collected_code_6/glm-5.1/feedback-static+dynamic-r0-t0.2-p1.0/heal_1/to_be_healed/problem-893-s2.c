#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct SubList {
    Node *head;
    struct SubList *next;
} SubList;

int *get_last_elements(SubList *list, int *count) {
    if (list == NULL) {
        *count = 0;
        return NULL;
    }

    int len = 0;
    SubList *curr = list;
    while (curr != NULL) {
        len++;
        curr = curr->next;
    }

    int *result = (int *)malloc(len * sizeof(int));
    if (result == NULL) {
        *count = 0;
        return NULL;
    }

    curr = list;
    for (int i = 0; i < len; i++) {
        if (curr->head == NULL) {
            free(result);
            *count = 0;
            return NULL;
        }

        Node *node = curr->head;
        while (node->next != NULL) {
            node = node->next;
        }
        result[i] = node->data;
        curr = curr->next;
    }

    *count = len;
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'sizes' can be declared as pointer to const [constParameterPointer]
 */
SubList *create_sublist(int **arrays, int *sizes, int sublist_count) {
    if (sublist_count == 0) return NULL;

    SubList *head = NULL;
    SubList *tail = NULL;

    for (int i = 0; i < sublist_count; i++) {
        SubList *s = (SubList *)malloc(sizeof(SubList));
        if (s == NULL) return NULL;

        s->next = NULL;
        s->head = NULL;

        Node *node_tail = NULL;
        for (int j = 0; j < sizes[i]; j++) {
            Node *n = (Node *)malloc(sizeof(Node));
            if (n == NULL) return NULL;

            n->data = arrays[i][j];
            n->next = NULL;

            if (s->head == NULL) {
                s->head = n;
                node_tail = n;
            } else {
                node_tail->next = n;
                node_tail = n;
            }
        }

        if (head == NULL) {
            head = s;
            tail = s;
        } else {
            tail->next = s;
            tail = s;
        }
    }

    return head;
}

void free_sublists(SubList *list) {
    while (list != NULL) {
        SubList *next_list = list->next;
        Node *curr = list->head;
        while (curr != NULL) {
            Node *next_node = curr->next;
            free(curr);
            curr = next_node;
        }
        free(list);
        list = next_list;
    }
}

int main(void) {
    int a1[] = {1, 2, 3};
    int a2[] = {4, 5};
    int a3[] = {6};
    int *arrays[] = {a1, a2, a3};
    int sizes[] = {3, 2, 1};

    SubList *list = create_sublist(arrays, sizes, 3);
    if (list == NULL) {
        return 1;
    }

    int count = 0;
    int *last_elements = get_last_elements(list, &count);

    if (last_elements != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%d\n", last_elements[i]);
        }
        free(last_elements);
    }

    free_sublists(list);

    return 0;
}