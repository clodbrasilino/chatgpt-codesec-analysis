#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void split_list_for_nth_element(Node **head, int n, Node ***result, int *size) {
    *size = 0;
    Node *current = *head;
    while (current != NULL) {
        Node *sublist = NULL;
        for (int i = 0; i < n && current != NULL; ++i) {
            append_node(&sublist, current->data);
            current = current->next;
        }
        result[*size] = sublist;
        (*size)++;
    }
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void free_lists(Node ***lists, int size) {
    for (int i = 0; i < size; ++i) {
        Node *current = lists[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(lists);
}

int main() {
    Node *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);
    append_node(&head, 6);

    int n = 3;
    int size = 0;
    Node ***result = (Node ***)malloc(5 * sizeof(Node **));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    split_list_for_nth_element(&head, n, result, &size);

    for (int i = 0; i < size; ++i) {
        print_list(result[i]);
    }

    free_lists(result, size);

    return 0;
}