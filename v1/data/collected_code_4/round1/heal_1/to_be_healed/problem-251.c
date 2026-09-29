#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insertBeforeEachElement(struct Node** head, int new_data) {
    struct Node* new_node;
    struct Node* temp = *head;
    struct Node* swap_node;

    while (temp != NULL) {
        new_node = (struct Node*) malloc(sizeof(struct Node));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        new_node->data = new_data;

        if(temp == *head){
            swap_node = temp->next;
            temp->next = new_node;
            new_node->next = swap_node;
            temp = new_node->next;
        }
        else {
            new_node->next = temp;
            temp = new_node->next->next;
        }
    }
}

void printList(struct Node *node) {
    while (node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* head = NULL;
    head = (struct Node*) malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'head' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head->data = 1;
    head->next = (struct Node*) malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*head.next' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head->next->data = 2;
    head->next->next = NULL;

    printf("Original Linked List is: ");
    printList(head);

    insertBeforeEachElement(&head, 0);

    printf("\nLinked List after inserting 0 before each element: ");
    printList(head);

    return 0;
}