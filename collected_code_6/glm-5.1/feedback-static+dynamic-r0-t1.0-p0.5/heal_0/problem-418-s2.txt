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

Node* append(Node* head, int data) {
    if (head == NULL) {
        return create_node(data);
    }
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = create_node(data);
    return head;
}

Node* find_max_length_sublist(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* max_start = head;
    int max_len = 1;

    Node* current_start = head;
    int current_len = 1;
    Node* current = head;

    while (current->next != NULL) {
        if (current->data <= current->next->data) {
            current_len++;
        } else {
            if (current_len > max_len) {
                max_len = current_len;
                max_start = current_start;
            }
            current_start = current->next;
            current_len = 1;
        }
        current = current->next;
    }

    if (current_len > max_len) {
        max_start = current_start;
    }

    return max_start;
}

void print_sublist(Node* start) {
    if (start == NULL) {
        return;
    }
    Node* current = start;
    while (current != NULL) {
        printf("%d ", current->data);
        if (current->next != NULL && current->data > current->next->data) {
            break;
        }
        current = current->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    Node* head = NULL;
    
    head = append(head, 1);
    head = append(head, 2);
    head = append(head, 3);
    head = append(head, 1);
    head = append(head, 2);
    head = append(head, 3);
    head = append(head, 4);
    head = append(head, 2);

    Node* max_sublist = find_max_length_sublist(head);
    
    print_sublist(max_sublist);

    free_list(head);

    return 0;
}