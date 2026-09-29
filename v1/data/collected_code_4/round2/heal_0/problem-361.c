#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int *data;
    struct Node *next;
} Node;

void removeEmptyLists(Node **head) {
    Node *temp = *head, *prev = *head;

    while(temp != NULL) {
        if(temp->data == NULL) {
            if(temp == *head) {
                *head = temp->next;
                free(temp);
                temp = *head;
            }
            else {
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }
        }
        else {
            prev = temp;
            temp = temp->next;
        }
       
    }
}

int main() {
    Node *head = NULL;
    
    // Fill the list of lists here..
    // Don't forget to dynamically allocate the memory for every new Node and their data ..
  
    removeEmptyLists(&head);
  
    // Print the elements of the lists or do anything else here ..
    // Don't forget to free all dynamically allocated memory at the end ..

    return 0;
}