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

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

Node *remove_tuples_length_k(Node *head, int k) {
    if (head == NULL || k <= 0) {
        return head;
    }

    Node *dummy = create_node(0);
    if (dummy == NULL) {
        return head;
    }
    dummy->next = head;

    Node *prev = dummy;
    Node *current = head;

    while (current != NULL) {
        int count = 0;
        Node *runner = current;
        while (runner != NULL && count < k) {
            runner = runner->next;
            count++;
        }

        if (count == k) {
            Node *temp = current;
            for (int i = 0; i < k; i++) {
                Node *next = temp->next;
                free(temp);
                temp = next;
            }
            prev->next = runner;
            current = runner;
        } else {
            prev = current;
            current = current->next;
        }
    }

    head = dummy->next;
    free(dummy);
    return head;
}

int main(void) {
    Node *head = NULL;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        append_node(&head, values[i]);
    }

    printf("Original list: ");
    print_list(head);

    int k = 3;
    head = remove_tuples_length_k(head, k);

    printf("After removing tuples of length %d: ", k);
    print_list(head);

    free_list(head);
    return 0;
}