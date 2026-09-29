#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

// Node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to add a new node to the beginning of a linked list
void push(Node** head, int data) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    Node* newNode = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

// Function to create a new list taking alternate elements from another given list
Node* createAlternateList(Node* originalList) {
    if (originalList == NULL) {
        return NULL;
    }
    
    Node* current = originalList;
    Node* alternateList = NULL;
    Node* tail = NULL;
    int count = 0;
    
    while (current != NULL) {
        if (count % 2 == 0) {
            push(&alternateList, current->data);
            if (tail == NULL) {
                tail = alternateList;
            }
        }
        current = current->next;
        count++;
    }
    
    if (tail != NULL) {
        tail->next = NULL;
    }
    
    return alternateList;
}

// Function to print the elements of a linked list
void printList(Node* list) {
    Node* temp = list;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    // Example usage
    Node* originalList = NULL;
    push(&originalList, 6);
    push(&originalList, 5);
    push(&originalList, 4);
    push(&originalList, 3);
    push(&originalList, 2);
    push(&originalList, 1);
    
    printf("Original List: ");
    printList(originalList);
    
    Node* alternateList = createAlternateList(originalList);
    
    printf("Alternate List: ");
    printList(alternateList);
    
    return 0;
}