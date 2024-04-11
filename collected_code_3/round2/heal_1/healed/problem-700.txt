#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int countRange(struct Node* head, int min, int max) {
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
    if(temp == NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    temp->data = data;
    temp->next = NULL;
    return temp;
}

int main() {
    struct Node* head = newNode(10);
    head->next = newNode(15);
    head->next->next = newNode(20);
    head->next->next->next = newNode(25);
    head->next->next->next->next = newNode(30);

    int count = countRange(head, 15, 30);
    printf("Number of elements in range 15 to 30 is %d\n", count);

    return 0;
}