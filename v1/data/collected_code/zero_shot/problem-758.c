#include <stdio.h>

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
    
    // Initialize the linked list with some data
    head = (Node*)malloc(sizeof(Node));
    head->data = 1;
    
    Node* second = (Node*)malloc(sizeof(Node));
    second->data = 2;
    
    Node* third = (Node*)malloc(sizeof(Node));
    third->data = 1;
    
    Node* fourth = (Node*)malloc(sizeof(Node));
    fourth->data = 3;
    
    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = NULL;
    
    int uniqueLists = countUniqueLists(head);
    printf("Number of unique lists: %d", uniqueLists);
    
    // Free the dynamically allocated memory
    Node* temp;
    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}