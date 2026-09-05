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

Node *divide_lists(Node *list1, Node *list2) {
    Node *result_head = NULL;
    Node *result_tail = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list2->data == 0) {
            break;
        }

        Node *new_node = create_node(list1->data / list2->data);

        if (result_head == NULL) {
            result_head = new_node;
            result_tail = new_node;
        } else {
            result_tail->next = new_node;
            result_tail = new_node;
        }

        list1 = list1->next;
        list2 = list2->next;
    }

    return result_head;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node *list1 = create_node(10);
    list1->next = create_node(20);
    list1->next->next = create_node(30);

    Node *list2 = create_node(2);
    list2->next = create_node(5);
    list2->next->next = create_node(0);

    Node *result = divide_lists(list1, list2);

    Node *current = result;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}