#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int count_in_range(Node *head, int lower, int upper) {
    int count = 0;
    Node *current = head;
    
    while (current != NULL) {
        if (current->data >= lower && current->data <= upper) {
            count++;
        }
        current = current->next;
    }
    
    return count;
}

Node *create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
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
    Node *head = NULL;
    Node *tail = NULL;
    const int values[] = {5, 12, 3, 8, 15, 7, 20, 1, 10, 18};
    int i;
    
    for (i = 0; i < 10; i++) {
        Node *new_node = create_node(values[i]);
        if (new_node == NULL) {
            free_list(head);
            return 1;
        }
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    
    int result = count_in_range(head, 5, 15);
    printf("%d\n", result);
    
    free_list(head);
    return 0;
}