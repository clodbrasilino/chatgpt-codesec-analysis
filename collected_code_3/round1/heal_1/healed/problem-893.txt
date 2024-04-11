#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    if (new_node != NULL) {
        new_node->data  = new_data;
        new_node->next = (*head_ref);
        (*head_ref)    = new_node;
    }
}

int getLast(struct Node* head) {
    struct Node* temp = head;
    if(head){
        while (temp->next != NULL) {
            temp = temp->next;
        }
        return temp->data;
    }
    return -1;
}

int main() {
    struct Node* head = NULL;
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    push(&head, 40);
    push(&head, 50);
    int last_element = getLast(head);
    if(last_element != -1)
    printf("Last element is %d\n", last_element);
    return 0;
}