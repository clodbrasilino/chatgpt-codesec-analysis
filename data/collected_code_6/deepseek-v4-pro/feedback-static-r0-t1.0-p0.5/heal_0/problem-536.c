#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
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
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int select_nth_item(Node *head, int n, int *result) {
    if (head == NULL || result == NULL || n <= 0) {
        return 0;
    }
    Node *current = head;
    int count = 1;
    while (current != NULL && count < n) {
        current = current->next;
        count++;
    }
    if (current == NULL) {
        return 0;
    }
    *result = current->data;
    return 1;
}

int main(void) {
    Node *list = NULL;
    int values[] = {10, 20, 30, 40, 50};
    int num_values = sizeof(values) / sizeof(values[0]);
    int i;
    int result;
    int status;

    for (i = 0; i < num_values; i++) {
        append_node(&list, values[i]);
    }

    status = select_nth_item(list, 3, &result);
    if (status == 1) {
        printf("3rd item: %d\n", result);
    } else {
        printf("Failed to get 3rd item\n");
    }

    status = select_nth_item(list, 10, &result);
    if (status == 1) {
        printf("10th item: %d\n", result);
    } else {
        printf("Failed to get 10th item\n");
    }

    status = select_nth_item(list, 0, &result);
    if (status == 1) {
        printf("0th item: %d\n", result);
    } else {
        printf("Failed to get 0th item\n");
    }

    free_list(list);
    return 0;
}