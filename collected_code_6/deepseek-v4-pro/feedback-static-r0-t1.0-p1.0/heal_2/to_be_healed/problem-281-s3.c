#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int are_elements_unique(Node* head) {
    if (head == NULL) {
        return 1;
    }

    Node* current = head;
    while (current != NULL) {
        Node* runner = current->next;
        while (runner != NULL) {
            if (current->data == runner->data) {
                return 0;
            }
            runner = runner->next;
        }
        current = current->next;
    }
    return 1;
}

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node* head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);
    head->next->next->next = create_node(40);
    head->next->next->next->next = create_node(20);

    if (are_elements_unique(head)) {
        printf("All elements are unique\n");
    } else {
        printf("Elements are not unique\n");
    }

    free_list(head);

    Node* head2 = create_node(5);
    head2->next = create_node(15);
    head2->next->next = create_node(25);
    head2->next->next->next = create_node(35);

    if (are_elements_unique(head2)) {
        printf("All elements are unique\n");
    } else {
        printf("Elements are not unique\n");
    }

    free_list(head2);

    /* Possible weaknesses found:
     *  Assignment 'head3=NULL', assigned value is 0
     */
    Node* head3 = NULL;

    /* Possible weaknesses found:
     *  Condition 'head3==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'head3==NULL' is always true
     */
    if (head3 == NULL) {
        printf("All elements are unique\n");
    } else if (are_elements_unique(head3)) {
        printf("All elements are unique\n");
    } else {
        printf("Elements are not unique\n");
    }

    return 0;
}