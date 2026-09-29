#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

int maxSubList(struct Node* head) {
    int maxCount = 0;
    int currentCount = 0;
    int prevData = head->data;
    struct Node* current = head;

    while (current != NULL) {
        if (current->data == prevData) {
            currentCount++;
        } else {
            if (currentCount > maxCount) {
                maxCount = currentCount;
            }
            currentCount = 1;
        }
        prevData = current->data;
        current = current->next;
    }

    if (currentCount > maxCount) {
        maxCount = currentCount;
    }

    return maxCount;
}

int main() {
    struct Node* head = NULL;
    push(&head, 10);
    push(&head, 10);
    push(&head, 10);
    push(&head, 20);
    push(&head, 20);
    push(&head, 30);
    push(&head, 30);
    push(&head, 30);
    push(&head, 30);

    printf("Length of maximum sublist is %d\n", maxSubList(head));

    return 0;
}