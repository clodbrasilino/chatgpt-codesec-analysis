#include<stdio.h>
#include<stdlib.h>

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
    while(current != NULL && current->next != NULL){
        current = current->next;
    }

    if(current != NULL){
        current->next = head;
    }
}

int main(){
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* second = (struct Node*)malloc(sizeof(struct Node));
    struct Node* third = (struct Node*)malloc(sizeof(struct Node));
    struct Node* fourth = (struct Node*)malloc(sizeof(struct Node));

    if(head != NULL){
        head->data = 1;
        head->next = second;
    }
    
    if(second != NULL){
        second->data = 2;
        second->next = third;
    }
    
    if(third != NULL){
        third->data = 3;
        third->next = fourth;
    }
    
    if(fourth != NULL){
        fourth->data = 4;
        fourth->next = NULL;
    } 

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