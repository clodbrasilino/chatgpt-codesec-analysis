#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    
    if(new_node == NULL){
        printf("Memory allocation failed\n");
        return;
    }
    
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void getElements(struct Node* head, int indices[], int len) {
    struct Node* temp = head;
    int counter = 0;
    
    for(int i = 0; i<len; i++){
        temp = head;
        counter = 0;
        
        while(temp!=NULL){
            if(counter == indices[i]){
                printf("Element at index %d: %d\n", indices[i], temp->data);
                break;
            }
            temp = temp->next;
            counter++;
        }
        
        if(temp == NULL){
            printf("Index out of bound\n");
        }
    }
}

int main() {
    struct Node* head = NULL;
    int indices[] = {0, 2, 3};
    int length = sizeof(indices)/sizeof(indices[0]);
    
    push(&head, 20);
    push(&head, 4);
    push(&head, 23);
    push(&head, 12);
    push(&head, 18);
    
    getElements(head, indices, length);
    
    return 0;
}