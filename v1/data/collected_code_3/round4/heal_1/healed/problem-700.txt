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
        if (current->data >= min && current->data <= max) {
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

    if(head == NULL || second == NULL || third == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    head->data = 1;
    head->next = second;
    
    second->data = 5;
    second->next = third;
   
    third->data = 10;
    third->next = NULL;

    printf("Number of elements in range 1 to 10: %d\n", countElementsInRange(head, 1, 10));

    free(head);
    free(second);
    free(third);

    return 0;
}