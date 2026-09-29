#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int countUniqueLists(struct Node* head) {
    int count = 0;
    struct Node* current = head;

    while (current != NULL) {
        struct Node* temp = current->next;

        while (temp != NULL) {
            if (current->data == temp->data) {
                break;
            }
            temp = temp->next;
        }

        if (temp == NULL) {
            count++;
        }
        current = current->next;
    }

    return count;
}

int main() {
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* second = (struct Node*)malloc(sizeof(struct Node));
    struct Node* third = (struct Node*)malloc(sizeof(struct Node));

    if (head == NULL || second == NULL || third == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 1;
    third->next = NULL;

    int uniqueLists = countUniqueLists(head);

    printf("Number of unique lists: %d\n", uniqueLists);

    free(head);
    free(second);
    free(third);

    return 0;
}