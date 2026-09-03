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

Node *divide_lists(Node *list1, Node *list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }
    
    Node *result = NULL;
    Node *current1 = list1;
    Node *current2 = list2;
    
    while (current1 != NULL && current2 != NULL) {
        if (current2->data == 0) {
            free_list(result);
            return NULL;
        }
        int quotient = current1->data / current2->data;
        append_node(&result, quotient);
        current1 = current1->next;
        current2 = current2->next;
    }
    
    return result;
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;
    Node *result = NULL;
    
    append_node(&list1, 10);
    append_node(&list1, 20);
    append_node(&list1, 30);
    
    append_node(&list2, 2);
    append_node(&list2, 4);
    append_node(&list2, 5);
    
    printf("List 1: ");
    print_list(list1);
    printf("List 2: ");
    print_list(list2);
    
    result = divide_lists(list1, list2);
    
    if (result != NULL) {
        printf("Result: ");
        print_list(result);
        free_list(result);
    } else {
        printf("Division failed\n");
    }
    
    free_list(list1);
    free_list(list2);
    
    return 0;
}