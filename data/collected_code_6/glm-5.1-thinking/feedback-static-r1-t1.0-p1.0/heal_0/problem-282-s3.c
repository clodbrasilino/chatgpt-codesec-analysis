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

int contains(Node *head, int value) {
    Node *current = head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Node *subtract_lists(Node *list1, Node *list2) {
    if (list1 == NULL) {
        return NULL;
    }
    Node *result = NULL;
    Node *current = list1;
    while (current != NULL) {
        if (!contains(list2, current->data)) {
            result = append(result, current->data);
        }
        current = current->next;
    }
    return result;
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
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;

    list1 = append(list1, 1);
    list1 = append(list1, 2);
    list1 = append(list1, 3);
    list1 = append(list1, 4);
    list1 = append(list1, 5);

    list2 = append(list2, 2);
    list2 = append(list2, 4);
    list2 = append(list2, 6);

    printf("List 1: ");
    print_list(list1);
    printf("List 2: ");
    print_list(list2);

    Node *result = subtract_lists(list1, list2);
    printf("List1 - List2: ");
    print_list(result);

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}