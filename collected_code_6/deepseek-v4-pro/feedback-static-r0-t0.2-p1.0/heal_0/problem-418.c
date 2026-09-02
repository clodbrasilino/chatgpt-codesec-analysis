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

Node *find_max_sublist(Node *head, int *max_length) {
    if (head == NULL || max_length == NULL) {
        if (max_length != NULL) {
            *max_length = 0;
        }
        return NULL;
    }

    Node *max_start = head;
    int current_length = 1;
    int max_len = 1;
    Node *current_start = head;
    Node *current = head->next;

    while (current != NULL) {
        if (current->data == current_start->data) {
            current_length++;
        } else {
            if (current_length > max_len) {
                max_len = current_length;
                max_start = current_start;
            }
            current_start = current;
            current_length = 1;
        }
        current = current->next;
    }

    if (current_length > max_len) {
        max_len = current_length;
        max_start = current_start;
    }

    *max_length = max_len;
    return max_start;
}

void print_sublist(Node *start, int length) {
    if (start == NULL || length <= 0) {
        return;
    }
    Node *current = start;
    for (int i = 0; i < length && current != NULL; i++) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node *list = NULL;
    int values[] = {1, 1, 2, 2, 2, 3, 4, 4, 4, 4, 5, 5};
    int num_values = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < num_values; i++) {
        append_node(&list, values[i]);
    }

    int max_length = 0;
    Node *max_sublist = find_max_sublist(list, &max_length);

    if (max_sublist != NULL && max_length > 0) {
        printf("Maximum sublist length: %d\n", max_length);
        printf("Maximum sublist: ");
        print_sublist(max_sublist, max_length);
    } else {
        printf("List is empty or invalid.\n");
    }

    free_list(list);
    return 0;
}