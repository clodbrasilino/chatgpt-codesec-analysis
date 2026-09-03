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

Node *subtract_lists(Node *list1, Node *list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }
    
    Node *result = NULL;
    Node *current1 = list1;
    Node *current2 = list2;
    
    while (current1 != NULL && current2 != NULL) {
        int diff = current1->data - current2->data;
        append_node(&result, diff);
        current1 = current1->next;
        current2 = current2->next;
    }
    
    while (current1 != NULL) {
        append_node(&result, current1->data);
        current1 = current1->next;
    }
    
    while (current2 != NULL) {
        append_node(&result, -current2->data);
        current2 = current2->next;
    }
    
    return result;
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
    Node *list1 = NULL;
    Node *list2 = NULL;
    Node *result = NULL;
    
    append_node(&list1, 10);
    append_node(&list1, 20);
    append_node(&list1, 30);
    append_node(&list1, 40);
    
    append_node(&list2, 5);
    append_node(&list2, 15);
    append_node(&list2, 25);
    
    result = subtract_lists(list1, list2);
    
    print_list(list1);
    print_list(list2);
    print_list(result);
    
    free_list(list1);
    free_list(list2);
    free_list(result);
    
    return 0;
}