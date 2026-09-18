#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int push(struct Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return -1;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return -1;
    }

    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;

    return 0;
}

void remove_evens(struct Node** head_ref) {
    if (head_ref == NULL || *head_ref == NULL) {
        return;
    }

    struct Node* current = *head_ref;
    struct Node* prev = NULL;

    while (current != NULL) {
        if (current->data % 2 == 0) {
            if (prev == NULL) {
                *head_ref = current->next;
                free(current);
                current = *head_ref;
            } else {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void free_list(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_list(const struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main(void) {
    struct Node* head = NULL;

    if (push(&head, 5) != 0 ||
        push(&head, 4) != 0 ||
        push(&head, 3) != 0 ||
        push(&head, 2) != 0 ||
        push(&head, 1) != 0) {
        free_list(head);
        return EXIT_FAILURE;
    }

    print_list(head);
    remove_evens(&head);
    print_list(head);

    free_list(head);

    return EXIT_SUCCESS;
}