#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void shiftFirstToEnd(struct Node** head_ref) {
    if (head_ref == NULL || *head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }

    struct Node* first = *head_ref;
    struct Node* last = *head_ref;

    while (last->next != NULL) {
        last = last->next;
    }

    *head_ref = first->next;
    first->next = NULL;
    last->next = first;
}

void initializeList(struct Node** head_ref, int arr[], int size) {
    if (size <= 0) {
        return;
    }

    *head_ref = (struct Node*)malloc(sizeof(struct Node));
    if (*head_ref == NULL) {
        return;
    }
    
    (*head_ref)->data = arr[0];
    (*head_ref)->next = NULL;

    struct Node* current = *head_ref;

    for (int i = 1; i < size; i++) {
        current->next = (struct Node*)malloc(sizeof(struct Node));
        if (current->next == NULL) {
            return;
        }
        current = current->next;
        current->data = arr[i];
        current->next = NULL;
    }
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void freeList(struct Node* node) {
    struct Node* temp;
    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp);
    }
}

int main(void) {
    struct Node* head = NULL;
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    initializeList(&head, arr, size);

    printf("Original list: ");
    printList(head);

    shiftFirstToEnd(&head);

    printf("List after shifting first element to end: ");
    printList(head);

    freeList(head);

    return 0;
}