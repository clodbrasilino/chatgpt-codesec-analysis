#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    if(new_node == NULL) {
        printf("Memory allocation failed.");
        return;
    }

    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void removeElements(struct Node *listA, struct Node *listB) {
    struct Node* temp1 = listA;
    struct Node* temp2;
    struct Node* prev = NULL;
    struct Node* temp_next;

    while(temp1 != NULL) {
        temp2 = listB;
        while(temp2 != NULL) {
            if(temp1->data == temp2->data) {
                if(prev == NULL) {
                    listA = temp1->next;
                    free(temp1);
                    temp1 = listA;
                } else {
                    temp_next = temp1->next;
                    prev->next = temp_next;
                    free(temp1);
                    temp1 = temp_next;
                    break;
                }
            } else {
                temp2 = temp2 -> next;
            }
        }

        if(temp2 == NULL) {
            prev = temp1;
            temp1 = temp1 ->next;
        }
    }
}

void printList(struct Node *node) {
    while(node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* listA = NULL;
    struct Node* listB = NULL; 

    push(&listA, 5);
    push(&listA, 9);
    push(&listA, 3);
    push(&listB, 1);
    push(&listB, 3);
    push(&listB, 5);

    puts("List A before removing common elements: ");
    printList(listA);
    puts("\nList B before removing common elements: ");
    printList(listB);

    removeElements(listA, listB);

    puts("\nList A after removing common elements: ");
    printList(listA);

    return 0;
}