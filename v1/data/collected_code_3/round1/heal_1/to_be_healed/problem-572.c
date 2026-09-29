#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void removeDuplicates(Node* head) {
    Node *current = head;
    Node *index = NULL;
    Node *temp = NULL;

    if(head == NULL) {
        return;
    }
    else {
        while(current != NULL) {
            temp = current;
            index = current->next;

            while(index != NULL) {
                if(current->data == index->data) {
                    temp->next = index->next;
                }
                else {
                    temp = index;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

void display(Node* head) {
    Node* temp = head;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main() {
    Node* head = createNode(1);
    /* Possible weaknesses found:
     *  dereference of NULL 'head' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next = createNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next = createNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next = createNode(3);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next->next = createNode(3);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next->next->next = createNode(4);

    printf("Initial list: ");
    display(head);
    printf("\n");

    removeDuplicates(head);

    printf("List after removing duplicates: ");
    display(head);
    printf("\n");

    return 0;
}