#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void replaceLastElement(struct Node** head1, struct Node* head2) {
    struct Node* temp = *head1;
    
    if(temp == NULL) {
        *head1 = head2;
        return;
    }
    
    while(temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->next = head2;
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    
    head1 = (struct Node*)malloc(sizeof(struct Node));
    
    if(head1 != NULL) {
        head1->data = 1;
        head1->next = NULL;
    }
    
    struct Node* second1 = (struct Node*)malloc(sizeof(struct Node));
    
    if(second1 != NULL) {
        second1->data = 2;
        second1->next = NULL;
    }
    
    struct Node* third1 = (struct Node*)malloc(sizeof(struct Node));
    
    if(third1 != NULL) {
        third1->data = 3;
        third1->next = NULL;
    }
    
    if(head1 != NULL && second1 != NULL) {
        head1->next = second1;
    }
    if(second1 != NULL && third1 != NULL) {
        second1->next = third1;
    }
    
    head2 = (struct Node*)malloc(sizeof(struct Node));
    
    if(head2 != NULL) {
        head2->data = 4;
        head2->next = NULL;
    }
    
    struct Node* second2 = (struct Node*)malloc(sizeof(struct Node));
    
    if(second2 != NULL) {
        second2->data = 5;
        second2->next = NULL;
    }
    
    struct Node* third2 = (struct Node*)malloc(sizeof(struct Node));
    
    if(third2 != NULL) {
        third2->data = 6;
        third2->next = NULL;
    }
    
    if(head2 != NULL && second2 != NULL) {
        head2->next = second2;
    }
    if(second2 != NULL && third2 != NULL) {
        second2->next = third2;
    }
    
    replaceLastElement(&head1, head2);
    
    struct Node* temp = head1;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    return 0;
}