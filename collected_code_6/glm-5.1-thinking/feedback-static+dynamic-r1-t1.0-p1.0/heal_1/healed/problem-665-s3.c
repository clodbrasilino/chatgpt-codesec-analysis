#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void shift_first_to_end(struct Node **head_ref) {
    if (head_ref == NULL || *head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }
    struct Node *first = *head_ref;
    struct Node *last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    *head_ref = first->next;
    first->next = NULL;
    last->next = first;
}

void free_list(struct Node *head) {
    while (head != NULL) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    struct Node *head = malloc(sizeof(struct Node));
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    head->data = 1;
    
    head->next = malloc(sizeof(struct Node));
    if (head->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    head->next->data = 2;

    head->next->next = malloc(sizeof(struct Node));
    if (head->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    head->next->next->data = 3;
    head->next->next->next = NULL;

    struct Node *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");

    shift_first_to_end(&head);

    curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");

    free_list(head);
    return EXIT_SUCCESS;
}