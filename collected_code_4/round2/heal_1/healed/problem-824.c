#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node * next;
}Node;

Node * deleteEven(Node * head){
    Node * prev = NULL;
    Node * current = head;
    Node * temp;

    while(current != NULL){
        if(current->data % 2 == 0){
            if(prev != NULL){
                prev->next = current->next;
            }else{
                head = current->next;
            }
            temp = current;
            current = current->next;
            free(temp);
        }else{
            prev = current;
            current = current->next;
        }
    }

    return head;
}

void printList(Node * head){
    Node * current = head;

    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(){
    Node * head = (Node*) malloc(sizeof(Node));
    Node * second = (Node*) malloc(sizeof(Node));
    Node * third = (Node*) malloc(sizeof(Node));

    if(head == NULL || second == NULL || third == NULL){
        printf("Memory not allocated.");
        return 0;
    }

    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    printList(head);

    head = deleteEven(head);

    printList(head);

    free(head);

    return 0;
}