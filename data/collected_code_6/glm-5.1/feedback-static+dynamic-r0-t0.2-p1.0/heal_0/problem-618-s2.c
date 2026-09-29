#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    Node *current = head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

Node *divide_lists(Node *list1, Node *list2) {
    Node *head = NULL;
    Node *tail = NULL;
    Node *p1 = list1;
    Node *p2 = list2;

    while (p1 != NULL && p2 != NULL) {
        if (p2->data == 0) {
            free_list(head);
            return NULL;
        }

        Node *new_node = create_node(p1->data / p2->data);

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        p1 = p1->next;
        p2 = p2->next;
    }

    return head;
}

int main(void) {
    Node *list1 = create_node(10);
    list1->next = create_node(20);
    list1->next->next = create_node(30);

    Node *list2 = create_node(2);
    list2->next = create_node(5);
    list2->next->next = create_node(3);

    Node *result = divide_lists(list1, list2);
    if (result != NULL) {
        Node *curr = result;
        while (curr != NULL) {
            printf("%d ", curr->data);
            curr = curr->next;
        }
        printf("\n");
        free_list(result);
    } else {
        printf("Division error\n");
    }

    free_list(list1);
    free_list(list2);

    return 0;
}