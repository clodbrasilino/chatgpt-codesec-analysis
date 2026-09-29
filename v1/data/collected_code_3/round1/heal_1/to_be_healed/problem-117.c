#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* createNode(char *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void convertToFloat(Node *head) {
    Node *temp = head;
    while(temp != NULL) {
        float f = atof(temp->data);
        printf("%f ", f);
        temp = temp->next;
    }
}

int main() {
    Node *head = createNode("10");
    head->next = createNode("20");
    head->next->next = createNode("30");
    head->next->next->next = createNode("40");

    convertToFloat(head);

    return 0;
}