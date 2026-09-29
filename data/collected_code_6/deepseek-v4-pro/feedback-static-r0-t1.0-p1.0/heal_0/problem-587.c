#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Tuple {
    int *data;
    int length;
} Tuple;

Tuple list_to_tuple(Node *head) {
    Tuple result;
    int length = 0;
    Node *current = head;
    
    while (current != NULL) {
        length++;
        current = current->next;
    }
    
    result.data = (int *)malloc(length * sizeof(int));
    if (result.data == NULL) {
        result.length = 0;
        return result;
    }
    
    result.length = length;
    current = head;
    for (int i = 0; i < length; i++) {
        result.data[i] = current->data;
        current = current->next;
    }
    
    return result;
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    int values[] = {10, 20, 30, 40, 50};
    
    for (int i = 0; i < 5; i++) {
        Node *new_node = (Node *)malloc(sizeof(Node));
        if (new_node == NULL) {
            return 1;
        }
        new_node->data = values[i];
        new_node->next = NULL;
        
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    
    Tuple tuple = list_to_tuple(head);
    
    if (tuple.data != NULL) {
        for (int i = 0; i < tuple.length; i++) {
            printf("%d ", tuple.data[i]);
        }
        printf("\n");
        free(tuple.data);
    }
    
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    
    return 0;
}