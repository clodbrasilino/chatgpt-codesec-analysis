#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int isPresent(struct Node* head, int value) {
    struct Node* current = head;
    while (current != NULL){
        if (current->data == value)
            return 1;
        current = current->next;
    }
    return 0;
}

struct Node* newNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if(newNode == NULL)
        return NULL;
    newNode->data  = data;
    newNode->next =  NULL;
    return newNode;
}

int main(){
    struct Node* head = newNode(20);
    if(head == NULL){
        return -1;
    }
    head->next = newNode(17);
    if(head->next == NULL){
        return -1;
    }
    head->next->next = newNode(15);
    if(head->next->next == NULL){
        return -1;
    }
    head->next->next->next = newNode(14);
    if(head->next->next->next == NULL){
        return -1;
    }
    
    printf("Element Present status : ");
    if(isPresent(head, 17)){
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}