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
        float num;
        if(sscanf(temp->data, "%f", &num) == 1) {
            printf("%.2f ", num);
        }
        temp = temp->next;
    }
}

int main() {
    Node *head = createNode("123");
    head->next = createNode("abc");
    head->next->next = createNode("456.78");
    head->next->next->next = createNode("xyz");
    head->next->next->next->next = createNode("900");

    convertToFloat(head);

    return 0;
}