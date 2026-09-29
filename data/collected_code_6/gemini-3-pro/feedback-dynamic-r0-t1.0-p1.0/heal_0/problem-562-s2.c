#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int maxSublistLength(struct Node* head) {
    if (head == NULL) {
        return 0;
    }
    
    int maxLength = 0;
    int currentLength = 1;
    struct Node* current = head;
    
    while (current->next != NULL) {
        if (current->data < current->next->data) {
            currentLength++;
        } else {
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
            currentLength = 1;
        }
        current = current->next;
    }
    
    if (currentLength > maxLength) {
        maxLength = currentLength;
    }
    
    return maxLength;
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (newNode == NULL) {
        return;
    }
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    struct Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    
    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 3);
    appendNode(&head, 1);
    appendNode(&head, 4);
    appendNode(&head, 5);
    appendNode(&head, 6);
    appendNode(&head, 7);
    appendNode(&head, 2);
    
    int max_len = maxSublistLength(head);
    
    printf("Max sublist length: %d\n", max_len);
    
    freeList(head);
    
    return 0;
}