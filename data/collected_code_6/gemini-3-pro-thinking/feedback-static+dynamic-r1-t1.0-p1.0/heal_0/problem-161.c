#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

bool isPresent(const struct Node* head, int data) {
    while (head != NULL) {
        if (head->data == data) {
            return true;
        }
        head = head->next;
    }
    return false;
}

void removeElements(struct Node** head_ref, const struct Node* remove_list) {
    if (head_ref == NULL || remove_list == NULL) {
        return;
    }

    struct Node** curr = head_ref;
    while (*curr != NULL) {
        if (isPresent(remove_list, (*curr)->data)) {
            struct Node* temp = *curr;
            *curr = (*curr)->next;
            free(temp);
        } else {
            curr = &((*curr)->next);
        }
    }
}

void pushNode(struct Node** head_ref, int data) {
    if (head_ref == NULL) {
        return;
    }
    
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    
    newNode->data = data;
    newNode->next = *head_ref;
    *head_ref = newNode;
}

void freeList(struct Node** head_ref) {
    if (head_ref == NULL) {
        return;
    }
    
    struct Node* current = *head_ref;
    struct Node* next = NULL;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

void printList(const struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    pushNode(&list1, 5);
    pushNode(&list1, 4);
    pushNode(&list1, 3);
    pushNode(&list1, 2);
    pushNode(&list1, 1);

    pushNode(&list2, 4);
    pushNode(&list2, 2);

    removeElements(&list1, list2);
    
    printList(list1);

    freeList(&list1);
    freeList(&list2);

    return EXIT_SUCCESS;
}