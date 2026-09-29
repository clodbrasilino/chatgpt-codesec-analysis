#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* modifiedRLE(Node* head) {
    if(head == NULL || head->next == NULL)
        return head;

    Node* prev = head;
    Node* curr = head->next;

    while(curr != NULL) {
        if(prev->data == curr->data) {
            int count = 2;
            while(curr->next != NULL && curr->next->data == prev->data) {
                count++;
                curr = curr->next;
            }
            Node* temp = createNode(count);
            if(!temp){
                return NULL;
            }
            prev->next = temp;
            prev->next->next = curr->next;
            free(curr);
        }
        prev = curr;
        if(curr){
            /* Possible weaknesses found:
             *  use after 'free' of 'curr' [CWE-416] [-Wanalyzer-use-after-free]
             */
            curr = curr->next;
        }
    }
    return head;
}

void printList(Node* head) {
    while(head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* head = createNode(1);
    if(!head){
        return -1;
    }
    Node* temp = createNode(1);
    if(!temp){
        return -1;
    }
    head->next = temp;
    temp = createNode(2);
    if(!temp){
        return -1;
    }
    head->next->next = temp;
    temp = createNode(2);
    if(!temp){
        return -1;
    }
    head->next->next->next = temp;
    temp = createNode(2);
    if(!temp){
        return -1;
    }
    head->next->next->next->next = temp;
    temp = createNode(3);
    if(!temp){
        return -1;
    }
    head->next->next->next->next->next = temp;

    printf("Original List: ");
    printList(head);

    head = modifiedRLE(head);

    printf("Modified RLE List: ");
    printList(head);

    return 0;
}