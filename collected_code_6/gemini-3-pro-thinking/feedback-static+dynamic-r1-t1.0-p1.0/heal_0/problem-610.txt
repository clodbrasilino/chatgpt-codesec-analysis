#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int append_node(struct Node** head, int data) {
    if (!head) {
        return -1;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) {
        return -1;
    }
    
    new_node->data = data;
    new_node->next = NULL;

    if (!*head) {
        *head = new_node;
        return 0;
    }

    struct Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
    
    return 0;
}

int remove_kth_element(struct Node** head, size_t k) {
    if (!head || !*head) {
        return -1;
    }

    if (k == 0) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return 0;
    }

    struct Node* current = *head;
    struct Node* previous = NULL;
    size_t index = 0;

    while (current && index < k) {
        previous = current;
        current = current->next;
        index++;
    }

    if (!current) {
        return -1;
    }

    previous->next = current->next;
    free(current);
    
    return 0;
}

void free_list(struct Node** head) {
    if (!head) {
        return;
    }
    
    struct Node* current = *head;
    while (current) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

void print_list(const struct Node* head) {
    const struct Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    struct Node* head = NULL;

    for (int i = 0; i < 5; i++) {
        if (append_node(&head, i) != 0) {
            free_list(&head);
            return EXIT_FAILURE;
        }
    }

    print_list(head);

    if (remove_kth_element(&head, 2) != 0) {
        fprintf(stderr, "Failed to remove element at index 2\n");
    }
    
    if (remove_kth_element(&head, 0) != 0) {
        fprintf(stderr, "Failed to remove element at index 0\n");
    }
    
    if (remove_kth_element(&head, 10) != 0) {
        fprintf(stderr, "Failed to remove element at index 10 (out of bounds expected)\n");
    }

    print_list(head);

    free_list(&head);

    return EXIT_SUCCESS;
}