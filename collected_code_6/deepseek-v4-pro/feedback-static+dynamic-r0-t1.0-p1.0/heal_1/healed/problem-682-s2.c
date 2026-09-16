#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(struct Node **head, int data) {
    struct Node *new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(struct Node *head) {
    struct Node *current = head;
    
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int list_to_number(struct Node *head) {
    int number = 0;
    struct Node *current = head;
    
    while (current != NULL) {
        number = number * 10 + current->data;
        current = current->next;
    }
    
    return number;
}

struct Node *number_to_list(int number) {
    struct Node *head = NULL;
    int digits[32];
    int count = 0;
    int i;
    
    if (number == 0) {
        append_node(&head, 0);
        return head;
    }
    
    while (number > 0) {
        digits[count] = number % 10;
        number /= 10;
        count++;
    }
    
    for (i = count - 1; i >= 0; i--) {
        append_node(&head, digits[i]);
    }
    
    return head;
}

struct Node *multiply_lists(struct Node *list1, struct Node *list2) {
    int num1 = list_to_number(list1);
    int num2 = list_to_number(list2);
    int result = num1 * num2;
    
    return number_to_list(result);
}

void print_list(struct Node *head) {
    struct Node *current = head;
    
    if (current == NULL) {
        printf("Empty list\n");
        return;
    }
    
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;
    struct Node *result = NULL;
    
    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 3);
    
    append_node(&list2, 4);
    append_node(&list2, 5);
    
    printf("List 1: ");
    print_list(list1);
    printf("List 2: ");
    print_list(list2);
    
    result = multiply_lists(list1, list2);
    
    printf("Product list: ");
    print_list(result);
    
    free_list(list1);
    free_list(list2);
    free_list(result);
    
    return 0;
}