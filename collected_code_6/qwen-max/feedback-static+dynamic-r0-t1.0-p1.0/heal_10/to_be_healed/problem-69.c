#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/* Possible weaknesses found:
 *  unknown type name 'bool'
 */
bool isSublist(Node *list, Node *sublist) {
    /* Possible weaknesses found:
     *  use of undeclared identifier 'true'
     */
    if (sublist == NULL) return true;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'false'
     */
    if (list == NULL) return false;

    Node *ptr1 = list;
    while (ptr1 != NULL) {
        Node *ptr2 = sublist;
        Node *temp = ptr1;

        /* Possible weaknesses found:
         *  use of undeclared identifier 'bool'
         *  Variable 'matched' is assigned a value that is never used. [unreadVariable]
         */
        bool matched = true;

        while (ptr2 != NULL && temp != NULL && ptr2->data == temp->data) {
            ptr2 = ptr2->next;
            temp = temp->next;
        }

        /* Possible weaknesses found:
         *  use of undeclared identifier 'true'
         */
        if (ptr2 == NULL) return true;

        ptr1 = ptr1->next;
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'false'
     */
    return false;
}

int main() {
    Node *list = createNode(1);
    list->next = createNode(2);
    list->next->next = createNode(3);
    list->next->next->next = createNode(4);
    list->next->next->next->next = createNode(5);

    Node *sublist = createNode(2);
    sublist->next = createNode(3);
    sublist->next->next = createNode(4);

    if (isSublist(list, sublist)) {
        printf("Sublist found\n");
    } else {
        printf("Sublist not found\n");
    }

    Node *current = list;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    current = sublist;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}