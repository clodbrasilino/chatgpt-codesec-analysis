#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node* next;
};

void push(struct node** head_ref, int new_data){
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if(!new_node)
        return;

    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

int getCount(struct node* head){
    int count = 0;
    struct node* current = head;
    while (current != NULL){
        count++;
        current = current->next;
    }
    return count;
}

struct node* maxSubList(struct node* head, int size){
    struct node* current = head;
    int count = getCount(head);
    if (size > count){
        return NULL;
    } else {
        for (int i = 0; i < count - size + 1; i++){
            current = current->next;
        }
        return current;
    }
}

int main() {
    struct node* head = NULL;
    push(&head, 20);
    push(&head, 4);
    push(&head, 15);
    push(&head, 35);
    
    struct node* subList = NULL;
    subList = maxSubList(head, 2);
    
    while (subList != NULL){
        printf("%d ", subList->data);
        subList = subList->next;
    }
    
    return 0;
}