#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* findMaxSublist(struct Node* head) {
    if(head == NULL) {
        return NULL;
    }

    struct Node* curr = head;
    struct Node* prev = NULL;
    struct Node* maxStart = NULL;
    struct Node* maxEnd = NULL;
    int maxLength = 0;
    int currLength = 1;

    while(curr->next != NULL) {
        if(curr->data == curr->next->data) {
            currLength++;
        } else {
            if(currLength > maxLength) {
                maxLength = currLength;
                maxStart = prev;
                maxEnd = curr;
            }
            currLength = 1;
        }

        prev = curr;
        curr = curr->next;
    }
 
    if(currLength > maxLength) {
        maxLength = currLength;
        maxStart = prev;
        maxEnd = curr;
    }

    if(maxStart != NULL && maxEnd != NULL) {
        maxEnd->next = NULL;
        return maxStart->next;
    } else {
        return NULL;
    }
}

int main() {
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* second = (struct Node*)malloc(sizeof(struct Node));
    struct Node* third = (struct Node*)malloc(sizeof(struct Node));
    struct Node* fourth = (struct Node*)malloc(sizeof(struct Node));

    if(head!=NULL){
        head->data = 1;
        head->next = second;
    }
    
    if(second!=NULL){
        second->data = 2;
        second->next = third;
    }

    if(third!=NULL){
        third->data = 2;
        third->next = fourth;
    }

    if(fourth!=NULL){
        fourth->data = 3;
        fourth->next = NULL;
    }

    struct Node* result = findMaxSublist(head);

    if(result == NULL) {
        printf("No sublist found");
    } else {
        struct Node* temp = result;

        while(temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
    }

    free(fourth);
    free(third);
    free(second);
    free(head);

    return 0;
}