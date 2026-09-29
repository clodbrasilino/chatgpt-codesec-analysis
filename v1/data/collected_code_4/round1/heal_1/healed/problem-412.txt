#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node_t;

Node_t* removeOdd(Node_t* head) {
    Node_t* prev = NULL;
    Node_t* node = head;
    
    while (node != NULL) {
        if (node->data % 2 != 0) {
            if (node == head) {
                head = node->next;
            }
            else {
                prev->next = node->next;
            }
            Node_t* temp = node;
            node = node->next;
            free(temp);
        }
        else {
            prev = node;
            node = node->next;
        }
    }
    
    return head;
}

Node_t* push(Node_t* head_ref, int new_data) {
    Node_t* new_node = (Node_t*)malloc(sizeof(Node_t));
   
    if(new_node){
        new_node->data = new_data;
        new_node->next = head_ref;
        head_ref = new_node;
    }

    return head_ref;
}

void printList(Node_t* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    Node_t* head = NULL;
    
    for (int i = 0; i < 5; i++) {
        head = push(head, i);
    }
      
    printf("Created Linked List: ");
    printList(head);

    head = removeOdd(head);

    printf("\nLinked List after removing all odd nodes: ");
    printList(head);
   
    return 0;
}