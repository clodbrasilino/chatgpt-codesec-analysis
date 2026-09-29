#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void removeElements(struct Node *listA, struct Node *listB) {
    struct Node* temp1 = listA;
    struct Node* temp2;
    struct Node* prev;

    while(temp1 != NULL) {
        temp2 = listB;
        while(temp2 != NULL) {
            if(temp1->data == temp2->data) {
                if(temp1->next == NULL) {
                    prev->next = NULL;
                    free(temp1);
                    return;
                } else {
                    /* Possible weaknesses found:
                     *  Access to field 'next' results in a dereference of an undefined pointer value (loaded from variable 'prev') [core.NullDereference]
                     */
                    prev->next = temp1->next;
                    free(temp1);
                }
            }
            temp2 = temp2 -> next;
        }

        prev = temp1;
        temp1 = temp1 -> next;        
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