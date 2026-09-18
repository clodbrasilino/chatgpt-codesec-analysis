#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int append(Node** head_ref, int data);
int remove_kth_element(Node** head_ref, int k);
void free_list(Node* head);
void print_list(Node* head);

int append(Node** head_ref, int data) {
    if (!head_ref) {
        return -1;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return -1;
    }
    
    new_node->data = data;
    new_node->next = NULL;

    if (!*head_ref) {
        *head_ref = new_node;
        return 0;
    }

    Node* temp = *head_ref;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new_node;
    
    return 0;
}

int remove_kth_element(Node** head_ref, int k) {
    if (!head_ref || !*head_ref || k < 0) {
        return -1;
    }

    Node* current = *head_ref;
    Node* previous = NULL;

    if (k == 0) {
        *head_ref = current->next;
        free(current);
        return 0;
    }

    for (int i = 0; i < k; i++) {
        if (!current) {
            return -1;
        }
        previous = current;
        current = current->next;
    }

    if (!current) {
        return -1;
    }

    previous->next = current->next;
    free(current);

    return 0;
}

void free_list(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print_list(Node* head) {
    while (head) {
        printf("%d\n", head->data);
        head = head->next;
    }
}

int main(void) {
    Node* head = NULL;

    for (int i = 0; i < 5; i++) {
        if (append(&head, i * 10) != 0) {
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (remove_kth_element(&head, 2) != 0) {
        free_list(head);
        return EXIT_FAILURE;
    }

    if (remove_kth_element(&head, 0) != 0) {
        free_list(head);
        return EXIT_FAILURE;
    }

    print_list(head);
    free_list(head);

    return EXIT_SUCCESS;
}