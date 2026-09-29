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

void free_list(Node* head) {
    Node* current = head;
    Node* next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

Node* get_nth_item(Node* head, int n) {
    if (head == NULL || n < 0) {
        return NULL;
    }
    
    Node* current = head;
    int count = 0;
    
    while (current != NULL) {
        if (count == n) {
            return current;
        }
        count++;
        current = current->next;
    }
    
    return NULL;
}

int main(void) {
    Node* head = create_node(10);
    head->next = create_node(20);
    head->next->next = create_node(30);
    head->next->next->next = create_node(40);
    head->next->next->next->next = create_node(50);

    int n = 2;
    Node* nth_node = get_nth_item(head, n);

    if (nth_node != NULL) {
        printf("%d\n", nth_node->data);
    } else {
        printf("Item not found\n");
    }

    free_list(head);

    return EXIT_SUCCESS;
}