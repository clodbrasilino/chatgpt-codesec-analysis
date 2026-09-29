#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int maxSubListLength(struct Node* head) {
    int maxCount = 0;
    while (head != NULL) {
        struct Node* temp = head;
        int count = 0;
        while (temp != NULL && temp->data == head->data) {
            count++;
            temp = temp->next;
        }
        if (count > maxCount) {
            maxCount = count;
        }
        head = head->next;
    }
    return maxCount;
}

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if(node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

int main() {
    struct Node* head = newNode(1);
    struct Node* current = head;
    if(current == NULL) {
        return 1;
    }

    current->next = newNode(1);
    if (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode(2);
    if (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode(2);
    if (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode(2);
    if (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode(3);
    if (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode(3);
    if (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode(3);
    if (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode(3);

    printf("Max length of sublist is %d\n", maxSubListLength(head));

    return 0;
}