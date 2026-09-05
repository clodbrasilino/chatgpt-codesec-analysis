#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

bool contains_value(const Node *head, int target)
{
    const Node *current = head;
    
    while (current != NULL) {
        if (current->data == target) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

Node *create_node(int value)
{
    Node *new_node = malloc(sizeof(Node));
    
    if (new_node == NULL) {
        return NULL;
    }
    
    new_node->data = value;
    new_node->next = NULL;
    
    return new_node;
}

void append_node(Node **head, int value)
{
    Node *new_node = create_node(value);
    
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

void free_list(Node *head)
{
    Node *current = head;
    Node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    Node *list = NULL;
    int target = 30;
    
    append_node(&list, 10);
    append_node(&list, 20);
    append_node(&list, 30);
    append_node(&list, 40);
    append_node(&list, 50);
    
    if (contains_value(list, target)) {
        printf("Value %d found in the list\n", target);
    } else {
        printf("Value %d not found in the list\n", target);
    }
    
    free_list(list);
    
    return 0;
}