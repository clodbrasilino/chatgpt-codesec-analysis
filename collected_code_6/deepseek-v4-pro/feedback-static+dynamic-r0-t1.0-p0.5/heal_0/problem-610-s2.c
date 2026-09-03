#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
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
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

int remove_kth_element(Node **head, int k) {
    if (head == NULL || *head == NULL || k <= 0) {
        return -1;
    }
    
    Node *temp = *head;
    
    if (k == 1) {
        *head = temp->next;
        free(temp);
        return 0;
    }
    
    Node *prev = NULL;
    int count = 1;
    
    while (temp != NULL && count < k) {
        prev = temp;
        temp = temp->next;
        count++;
    }
    
    if (temp == NULL) {
        return -1;
    }
    
    prev->next = temp->next;
    free(temp);
    return 0;
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

int main(void) {
    Node *head = NULL;
    
    append_node(&head, 10);
    append_node(&head, 20);
    append_node(&head, 30);
    append_node(&head, 40);
    append_node(&head, 50);
    
    printf("Original list: ");
    print_list(head);
    
    int k = 3;
    if (remove_kth_element(&head, k) == 0) {
        printf("List after removing %drd element: ", k);
        print_list(head);
    } else {
        printf("Failed to remove element at position %d\n", k);
    }
    
    k = 1;
    if (remove_kth_element(&head, k) == 0) {
        printf("List after removing %dst element: ", k);
        print_list(head);
    } else {
        printf("Failed to remove element at position %d\n", k);
    }
    
    k = 10;
    if (remove_kth_element(&head, k) == 0) {
        printf("List after removing %dth element: ", k);
        print_list(head);
    } else {
        printf("Failed to remove element at position %d\n", k);
    }
    
    free_list(head);
    return 0;
}