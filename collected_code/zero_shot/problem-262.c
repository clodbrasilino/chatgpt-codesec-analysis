#include<stdio.h>

struct Node{
    int data;
    struct Node* next;
};

void splitList(struct Node* head, int length_first_part){
    struct Node* temp = head;
    int count = 0;
    while(temp != NULL){
        count++;
        if(count == length_first_part){
            break;
        }
        temp = temp->next;
    }
    
    if(temp == NULL){
        return;
    }
    
    struct Node* new_head = temp->next;
    temp->next = NULL;
    
    struct Node* current = new_head;
    while(current->next != NULL){
        current = current->next;
    }
    
    current->next = head;
}

int main(){
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;
    struct Node* fourth = NULL;

    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));
    fourth = (struct Node*)malloc(sizeof(struct Node));

    head->data = 1;
    head->next = second;
    second->data = 2;
    second->next = third;
    third->data = 3;
    third->next = fourth;
    fourth->data = 4;
    fourth->next = NULL;

    splitList(head, 2);

    printf("First part of the list:\n");
    struct Node* temp = head;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\nSecond part of the list:\n");
    temp = second;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    
    return 0;
}