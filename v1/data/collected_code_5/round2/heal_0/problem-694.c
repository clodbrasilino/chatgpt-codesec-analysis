#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

//Function to insert unique items in the linked list
void insertUnique(struct Node** head, int data) {
    struct Node* current = *head;
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node -> data = data;
    new_node -> next = NULL;

    if(*head == NULL){
        *head = new_node;
    }
    else{
        while(current -> next != NULL){
            if(current -> data == data)
                return;
            current = current -> next;
        }
        if(current -> data != data)
            current -> next = new_node;
    }

}

//Function to print the linked list
void printList(struct Node *node) {
    while (node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
}

//Main function to handle the program logic
int main() {
    struct Node* head = NULL;
    
    int array[7] = {1, 2, 2, 3, 3, 4, 5};

    for(int i=0; i<7; i++){
        insertUnique(&head, array[i]);
    }
    
    printList(head);
   
    return 0;
}