#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* createNode(char *data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    
    if (newNode == NULL)
        return NULL;
        
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
    if (head == NULL)
        return -1;
        
    head->next = createNode("abc");
    
    if (head->next == NULL)
        return -1;
        
    head->next->next = createNode("456.78");
    
    if (head->next->next == NULL)
        return -1;
        
    head->next->next->next = createNode("xyz");
    
    if (head->next->next->next == NULL)
        return -1;
        
    head->next->next->next->next = createNode("900");
    
    if (head->next->next->next->next == NULL)
        return -1;
        
    convertToFloat(head);
    
    return 0;
}