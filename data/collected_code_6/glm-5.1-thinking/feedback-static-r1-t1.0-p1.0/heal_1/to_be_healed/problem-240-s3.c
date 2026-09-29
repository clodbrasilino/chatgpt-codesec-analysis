#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node *append(Node *head, int data) {
    Node *node = create_node(data);
    if (node == NULL) {
        return head;
    }
    if (head == NULL) {
        return node;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return head;
}

int replace_last_with_list(Node **list1, Node *list2) {
    if (list1 == NULL) {
        return -1;
    }
    if (*list1 == NULL) {
        *list1 = list2;
        return 0;
    }
    if ((*list1)->next == NULL) {
        free(*list1);
        *list1 = list2;
        return 0;
    }
    /* Possible weaknesses found:
     *  Assignment 'prev=NULL', assigned value is 0
     */
    Node *prev = NULL;
    Node *current = *list1;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    /* Possible weaknesses found:
     *  Possible null pointer dereference: prev [nullPointer]
     *  Null pointer dereference
     */
    prev->next = list2;
    free(current);
    return 0;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
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
    Node *list1 = NULL;
    list1 = append(list1, 1);
    list1 = append(list1, 2);
    list1 = append(list1, 3);

    Node *list2 = NULL;
    list2 = append(list2, 4);
    list2 = append(list2, 5);
    list2 = append(list2, 6);

    printf("List 1: ");
    print_list(list1);
    printf("List 2: ");
    print_list(list2);

    if (replace_last_with_list(&list1, list2) != 0) {
        fprintf(stderr, "Failed to replace last element\n");
        free_list(list1);
        free_list(list2);
        return 1;
    }

    printf("After replacement: ");
    print_list(list1);

    free_list(list1);

    return 0;
}