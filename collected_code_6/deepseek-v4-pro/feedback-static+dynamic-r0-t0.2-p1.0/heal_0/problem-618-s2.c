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

Node *divide_lists(Node *dividend, Node *divisor) {
    if (dividend == NULL || divisor == NULL) {
        return NULL;
    }
    
    Node *result = NULL;
    Node *current_dividend = dividend;
    Node *current_divisor = divisor;
    
    while (current_dividend != NULL && current_divisor != NULL) {
        if (current_divisor->data == 0) {
            free_list(result);
            return NULL;
        }
        int quotient = current_dividend->data / current_divisor->data;
        append_node(&result, quotient);
        current_dividend = current_dividend->next;
        current_divisor = current_divisor->next;
    }
    
    while (current_dividend != NULL) {
        append_node(&result, current_dividend->data);
        current_dividend = current_dividend->next;
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
    
    append_node(&list2, 2);
    append_node(&list2, 5);
    append_node(&list2, 10);
    
    result = divide_lists(list1, list2);
    
    if (result != NULL) {
        print_list(result);
        free_list(result);
    } else {
        printf("Division failed\n");
    }
    
    free_list(list1);
    free_list(list2);
    
    return 0;
}