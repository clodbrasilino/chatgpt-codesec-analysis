#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node** head_ref, int data) {
    Node* new_node = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    Node* last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

Node* find_max_ascending_sublist(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* max_start = head;
    int max_len = 1;

    Node* curr_start = head;
    int curr_len = 1;
    Node* curr = head;

    while (curr->next != NULL) {
        if (curr->next->data > curr->data) {
            curr_len++;
        } else {
            if (curr_len > max_len) {
                max_len = curr_len;
                max_start = curr_start;
            }
            curr_start = curr->next;
            curr_len = 1;
        }
        curr = curr->next;
    }

    if (curr_len > max_len) {
        max_start = curr_start;
    }

    return max_start;
}

void print_sublist(Node* start) {
    if (start == NULL) {
        return;
    }
    Node* curr = start;
    printf("%d", curr->data);
    int prev_data = curr->data;
    curr = curr->next;
    while (curr != NULL && curr->data > prev_data) {
        printf(" -> %d", curr->data);
        prev_data = curr->data;
        curr = curr->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    Node* head = NULL;

    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);
    append_node(&head, 2);
    append_node(&head, 3);

    const Node* max_sublist = find_max_ascending_sublist(head);

    if (max_sublist != NULL) {
        printf("Maximum ascending sublist starts at node with data: %d\n", max_sublist->data);
    } else {
        printf("List is empty.\n");
    }

    free_list(head);

    return 0;
}