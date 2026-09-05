#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

Node *remove_empty_lists(Node *head) {
    Node dummy;
    dummy.next = head;
    Node *prev = &dummy;
    Node *curr = head;

    while (curr != NULL) {
        /* Possible weaknesses found:
         *  Variable 'inner_head' can be declared as pointer to const [constVariablePointer]
         */
        Node *inner_head = (Node *)curr->data;
        if (inner_head == NULL) {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    return dummy.next;
}

Node *create_node(void *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
}

int main(void) {
    Node *empty1 = NULL;
    Node *empty2 = NULL;

    Node *non_empty1 = create_node((void *)0x1);
    Node *non_empty2 = create_node((void *)0x2);

    Node *list1 = create_node((void *)empty1);
    Node *list2 = create_node((void *)non_empty1);
    Node *list3 = create_node((void *)empty2);
    Node *list4 = create_node((void *)non_empty2);

    list1->next = list2;
    list2->next = list3;
    list3->next = list4;

    Node *head = list1;

    head = remove_empty_lists(head);

    Node *curr = head;
    while (curr != NULL) {
        if (curr->data != NULL) {
            printf("Non-empty list found\n");
        }
        curr = curr->next;
    }

    free_list(non_empty1);
    free_list(non_empty2);
    free_list(head);

    return 0;
}