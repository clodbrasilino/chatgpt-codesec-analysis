#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data){
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* subtractLists(Node* first, Node* second) {
    Node* result = NULL; 
    Node *temp, *prev = NULL;
    int diff;

    while (first != NULL) {
        diff = first->data;
        if(second != NULL) {
            diff -= second->data;
            second = second->next;
        }

        temp = newNode(diff);

        if (result == NULL) {
            result = temp;
        } else {
            prev->next = temp;
        }

        prev = temp;
        first = first->next;
    }

    return result;
}

void printList(struct Node* node) {
    while(node != NULL) {
        printf("%d ", node->data); 
        node = node->next;
    }
}

int main() {
    Node* first = NULL;
    Node* second = NULL;
    Node* res = NULL;

    first = newNode(1);
    /* Possible weaknesses found:
     *  dereference of NULL 'first' [CWE-476] [-Wanalyzer-null-dereference]
     */
    first->next = newNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    first->next->next = newNode(8);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    first->next->next->next = newNode(6);

    second = newNode(4);
    /* Possible weaknesses found:
     *  dereference of NULL 'second' [CWE-476] [-Wanalyzer-null-dereference]
     */
    second->next = newNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    second->next->next = newNode(5);

    res = subtractLists(first, second);
    printList(res);

    return 0;
}