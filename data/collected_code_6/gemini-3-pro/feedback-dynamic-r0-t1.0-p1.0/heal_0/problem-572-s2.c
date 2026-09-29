#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void removeDuplicates(struct Node** head_ref) {
    if (head_ref == NULL || *head_ref == NULL) {
        return;
    }

    struct Node* current = *head_ref;
    struct Node* prev = NULL;
    struct Node* temp;
    int count;

    while (current != NULL) {
        count = 0;
        temp = *head_ref;
        
        while (temp != NULL) {
            if (temp->data == current->data) {
                count++;
            }
            temp = temp->next;
        }

        if (count == 2) {
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

void push(struct Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return;
    }

    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void freeList(struct Node** head_ref) {
    if (head_ref == NULL) {
        return;
    }

    struct Node* current = *head_ref;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

int main() {
    struct Node* head = NULL;

    push(&head, 12);
    push(&head, 11);
    push(&head, 12);
    push(&head, 21);
    push(&head, 41);
    push(&head, 43);
    push(&head, 21);

    printList(head);

    removeDuplicates(&head);

    printList(head);

    freeList(&head);

    return 0;
}