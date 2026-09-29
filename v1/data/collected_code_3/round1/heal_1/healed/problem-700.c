#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int countElementsInRange(struct Node* head, int min, int max) {
    struct Node* current = head;
    int count = 0;
    while (current != NULL) {
        if (current->data >= min && current->data <= max)
            count++;
        current = current->next;
    }
    return count;
}

struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    if(temp != NULL) {
        temp->data = data;
        temp->next = NULL;
    }
    return temp;
}

int main() {
    struct Node* head = newNode(10);
    if (head == NULL)
        return 1;
    head->next = newNode(15);
    if (head->next == NULL)
        return 1;
    head->next->next = newNode(20);
    if (head->next->next == NULL)
        return 1;
    head->next->next->next = newNode(25);
    if (head->next->next->next == NULL)
        return 1;
    head->next->next->next->next = newNode(30);
    if (head->next->next->next->next == NULL)
        return 1;

    int count = countElementsInRange(head, 15, 30);
    printf("Number of elements in range : %d", count);

    return 0;
}