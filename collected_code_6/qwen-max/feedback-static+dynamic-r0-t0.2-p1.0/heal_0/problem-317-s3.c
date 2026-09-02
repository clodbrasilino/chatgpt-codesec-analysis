#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int freq;
    struct Node *next;
} Node;

Node* createNode(int val, int freq) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->val = val;
    newNode->freq = freq;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

Node* encode(Node *head) {
    if (head == NULL || head->next == NULL) return head;
    
    Node *current = head;
    Node *encodedHead = NULL;
    Node **lastEncoded = &encodedHead;
    
    while (current != NULL) {
        int count = 1;
        while (current->next != NULL && current->val == current->next->val) {
            count++;
            current = current->next;
        }
        
        *lastEncoded = createNode(count, current->val);
        if (*lastEncoded == NULL) return NULL;
        lastEncoded = &(*lastEncoded)->next;
        
        current = current->next;
    }
    
    return encodedHead;
}

int main() {
    Node *head = createNode(1, 0);
    head->next = createNode(1, 0);
    head->next->next = createNode(2, 0);
    head->next->next->next = createNode(2, 0);
    head->next->next->next->next = createNode(2, 0);
    head->next->next->next->next->next = createNode(3, 0);

    Node *encoded = encode(head);
    Node *current = encoded;
    while (current != NULL) {
        printf("(%d, %d) ", current->freq, current->val);
        current = current->next;
    }
    printf("\n");

    freeList(encoded);
    freeList(head);
    return 0;
}