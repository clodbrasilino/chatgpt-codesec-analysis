#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void append(Node **head, int value) {
    Node *new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int count_same_pairs(Node *list1, Node *list2, Node *list3) {
    int count = 0;
    Node *p1 = list1;
    Node *p2 = list2;
    Node *p3 = list3;

    while (p1 != NULL && p2 != NULL && p3 != NULL) {
        if (p1->data == p2->data && p2->data == p3->data) {
            count++;
            p1 = p1->next;
            p2 = p2->next;
            p3 = p3->next;
        } else {
            if (p1->data <= p2->data && p1->data <= p3->data) {
                p1 = p1->next;
            } else if (p2->data <= p1->data && p2->data <= p3->data) {
                p2 = p2->next;
            } else {
                p3 = p3->next;
            }
        }
    }
    return count;
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;
    Node *list3 = NULL;

    int arr1[] = {1, 3, 5, 7, 9};
    int arr2[] = {1, 2, 3, 5, 7, 9, 11};
    int arr3[] = {1, 3, 5, 7, 8, 9, 12};

    for (size_t i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
        append(&list1, arr1[i]);
    }
    for (size_t i = 0; i < sizeof(arr2) / sizeof(arr2[0]); i++) {
        append(&list2, arr2[i]);
    }
    for (size_t i = 0; i < sizeof(arr3) / sizeof(arr3[0]); i++) {
        append(&list3, arr3[i]);
    }

    int result = count_same_pairs(list1, list2, list3);
    printf("%d\n", result);

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}