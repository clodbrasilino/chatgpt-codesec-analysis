#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
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
            /* Possible weaknesses found:
             *  use after 'free' of 'temp1' [CWE-416] [-Wanalyzer-use-after-free]
             */
            if(temp1->data == temp2->data) {
                if(temp1->next == NULL) {
                    /* Possible weaknesses found:
                     *  use of uninitialized value 'prev' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
                     */
                    prev->next = NULL;
                    free(temp1);
                    return;
                } else {
                    /* Possible weaknesses found:
                     *  use of uninitialized value 'prev' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
                     */
                    prev->next = temp1->next;
                    free(temp1);
                }
            }
            temp2 = temp2 -> next;
        }

        prev = temp1;
        /* Possible weaknesses found:
         *  use after 'free' of 'temp1' [CWE-416] [-Wanalyzer-use-after-free]
         */
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