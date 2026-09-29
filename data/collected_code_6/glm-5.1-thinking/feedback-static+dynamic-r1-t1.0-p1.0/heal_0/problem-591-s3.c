#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void swap_first_last(struct Node **head_ref) {
    if (head_ref == NULL || *head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }
    struct Node *first = *head_ref;
    struct Node *second_last = *head_ref;
    while (second_last->next->next != NULL) {
        second_last = second_last->next;
    }
    struct Node *last = second_last->next;
    if (first->next == last) {
        last->next = first;
        first->next = NULL;
        *head_ref = last;
    } else {
        last->next = first->next;
        second_last->next = first;
        first->next = NULL;
        *head_ref = last;
    }
}

struct Node *create_node(int data) {
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

void print_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    struct Node *head = create_node(1);
    if (head == NULL) return EXIT_FAILURE;
    
    head->next = create_node(2);
    if (head->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    
    head->next->next = create_node(3);
    if (head->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    
    head->next->next->next = create_node(4);
    if (head->next->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    print_list(head);
    swap_first_last(&head);
    print_list(head);

    free_list(head);
    head = NULL;

    struct Node *single = create_node(10);
    if (single == NULL) return EXIT_FAILURE;
    
    print_list(single);
    swap_first_last(&single);
    print_list(single);
    
    free_list(single);
    single = NULL;

    return EXIT_SUCCESS;
}