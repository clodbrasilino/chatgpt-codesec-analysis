#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int *data;
    size_t size;
    struct Node *next;
} Node;

/* Possible weaknesses found:
 *  Parameter 'data' can be declared as pointer to const [constParameterPointer]
 */
Node *create_node(int *data, size_t size) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = (int *)malloc(size * sizeof(int));
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        node->data[i] = data[i];
    }
    node->size = size;
    node->next = NULL;
    return node;
}

/* Possible weaknesses found:
 *  Parameter 'b' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'a' can be declared as pointer to const [constParameterPointer]
 */
bool lists_equal(int *a, size_t a_size, int *b, size_t b_size) {
    if (a_size != b_size) {
        return false;
    }
    for (size_t i = 0; i < a_size; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

Node *remove_duplicates(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    Node *current = head;
    while (current != NULL && current->next != NULL) {
        Node *runner = current;
        while (runner->next != NULL) {
            if (lists_equal(current->data, current->size, runner->next->data, runner->next->size)) {
                Node *temp = runner->next;
                runner->next = runner->next->next;
                free(temp->data);
                free(temp);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
    return head;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("[");
        for (size_t i = 0; i < current->size; i++) {
            printf("%d", current->data[i]);
            if (i < current->size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        current = current->next;
    }
}

int main(void) {
    Node *head = NULL;
    int a1[] = {1, 2, 3};
    int a2[] = {4, 5};
    int a3[] = {1, 2, 3};
    int a4[] = {6};
    int a5[] = {4, 5};

    Node *n1 = create_node(a1, 3);
    if (n1 == NULL) { return 1; }
    head = n1;

    Node *n2 = create_node(a2, 2);
    if (n2 == NULL) { free_list(head); return 1; }
    n1->next = n2;

    Node *n3 = create_node(a3, 3);
    if (n3 == NULL) { free_list(head); return 1; }
    n2->next = n3;

    Node *n4 = create_node(a4, 1);
    if (n4 == NULL) { free_list(head); return 1; }
    n3->next = n4;

    Node *n5 = create_node(a5, 2);
    if (n5 == NULL) { free_list(head); return 1; }
    n4->next = n5;

    printf("Original:\n");
    print_list(head);

    head = remove_duplicates(head);

    printf("\nAfter removing duplicates:\n");
    print_list(head);

    free_list(head);

    return 0;
}