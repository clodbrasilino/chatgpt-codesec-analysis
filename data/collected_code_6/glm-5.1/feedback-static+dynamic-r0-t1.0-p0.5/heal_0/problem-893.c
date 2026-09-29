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

int *get_last_elements(SubList *list, size_t *out_size) {
    if (list == NULL || out_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    SubList *curr = list;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }

    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    curr = list;
    for (size_t i = 0; i < count; i++) {
        if (curr->head == NULL) {
            free(result);
            return NULL;
        }
        Node *node = curr->head;
        while (node->next != NULL) {
            node = node->next;
        }
        result[i] = node->data;
        curr = curr->next;
    }

    *out_size = count;
    return result;
}

Node *create_node(int data) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        exit(EXIT_FAILURE);
    }
    n->data = data;
    n->next = NULL;
    return n;
}

SubList *create_sublist(Node *head) {
    SubList *sl = (SubList *)malloc(sizeof(SubList));
    if (sl == NULL) {
        exit(EXIT_FAILURE);
    }
    sl->head = head;
    sl->next = NULL;
    return sl;
}

void free_nodes(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void free_sublists(SubList *head) {
    while (head != NULL) {
        SubList *tmp = head;
        free_nodes(head->head);
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    Node *n1 = create_node(1);
    n1->next = create_node(2);
    n1->next->next = create_node(3);

    Node *n2 = create_node(4);
    n2->next = create_node(5);

    Node *n3 = create_node(6);

    SubList *sl = create_sublist(n1);
    sl->next = create_sublist(n2);
    sl->next->next = create_sublist(n3);

    size_t size = 0;
    int *last_elements = get_last_elements(sl, &size);

    if (last_elements != NULL) {
        for (size_t i = 0; i < size; i++) {
            printf("%d\n", last_elements[i]);
        }
        free(last_elements);
    }

    free_sublists(sl);

    return 0;
}