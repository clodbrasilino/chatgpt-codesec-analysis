#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int countUniqueLists(Node* head) {
    int count = 0;
    
    while(head != NULL) {
        Node* current = head->next;
        Node* nextUnique = head;
        
        while(current != NULL) {
            if(current->data == nextUnique->data) {
                nextUnique->next = current->next;
                Node* temp = current;
                current = current->next;
                free(temp);
            } else {
                nextUnique = current;
                current = current->next;
            }
        }
        
        head = head->next;
        count++;
    }
    
    return count;
}

int main() {
    Node* head = NULL;
    
    head = (Node*)malloc(sizeof(Node));
    
    if (!head) {
        printf("Memory allocation error\n");
        return -1;
    }
    head->data = 1;
    
    Node* second = (Node*)malloc(sizeof(Node));
    
    if (!second) {
        printf("Memory allocation error\n");
        return -1;
    }
    second->data = 2;
   
    Node* third = (Node*)malloc(sizeof(Node));
  
    if (!third) {
        printf("Memory allocation error\n");
        return -1;
    }
    third->data = 1;
    
    Node* fourth = (Node*)malloc(sizeof(Node));
    
    if (!fourth) {
        printf("Memory allocation error\n");
        return -1;
    }
    fourth->data = 3;
    
    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = NULL;
    
    int uniqueLists = countUniqueLists(head);
    printf("Number of unique lists: %d", uniqueLists);
    
    Node* temp;
    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}