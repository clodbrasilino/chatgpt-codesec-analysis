#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

int append_node(Node **head, int data) {
    if (head == NULL) {
        return -1;
    }
    Node *node = create_node(data);
    if (node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = node;
        return 0;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 0;
}

void free_list(Node **head) {
    if (head == NULL) {
        return;
    }
    Node *current = *head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

Node *add_lists(Node *list1, Node *list2) {
    Node *result = NULL;
    Node **tail = &result;

    while (list1 != NULL && list2 != NULL) {
        Node *node = create_node(list1->data + list2->data);
        if (node == NULL) {
            free_list(&result);
            return NULL;
        }
        *tail = node;
        tail = &node->next;
        list1 = list1->next;
        list2 = list2->next;
    }

    Node *remaining = (list1 != NULL) ? list1 : list2;
    while (remaining != NULL) {
        Node *node = create_node(remaining->data);
        if (node == NULL) {
            free_list(&result);
            return NULL;
        }
        *tail = node;
        tail = &node->next;
        remaining = remaining->next;
    }

    return result;
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;
    Node *sum = NULL;

    if (append_node(&list1, 1) != 0 ||
        append_node(&list1, 2) != 0 ||
        append_node(&list1, 3) != 0 ||
        append_node(&list2, 4) != 0 ||
        append_node(&list2, 5) != 0) {
        free_list(&list1);
        free_list(&list2);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    sum = add_lists(list1, list2);
    if (sum == NULL && (list1 != NULL || list2 != NULL)) {
        free_list(&list1);
        free_list(&list2);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    print_list(list1);
    print_list(list2);
    print_list(sum);

    free_list(&list1);
    free_list(&list2);
    free_list(&sum);

    return 0;
}