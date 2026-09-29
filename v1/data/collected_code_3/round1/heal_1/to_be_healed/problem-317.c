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
            prev->next = createNode(count);
            /* Possible weaknesses found:
             *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
             */
            prev->next->next = curr->next;
        }
        prev = curr;
        /* Possible weaknesses found:
         *  leak of 'curr' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        curr = curr->next;
    }
    /* Possible weaknesses found:
     *  leak of 'prev' [CWE-401] [-Wanalyzer-malloc-leak]
     */
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
    /* Possible weaknesses found:
     *  dereference of NULL 'head' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next = createNode(1);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next = createNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next = createNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next->next = createNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next->next->next = createNode(3);

    printf("Original List: ");
    printList(head);

    head = modifiedRLE(head);

    printf("Modified RLE List: ");
    printList(head);

    return 0;
}