#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int count;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

void addNode(struct Node** head, int data) {
    struct Node* temp = *head;
    while(temp != NULL) {
        if(temp->data == data) {
            temp->count += 1;
            return;
        }
        temp = temp->next;
    }
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

int findMaxFreq(struct Node* head) {
    int max = 0;
    int data;
    while(head != NULL) {
        if(head->count > max) {
            max = head->count;
            data = head->data;
        }
        head = head->next;
    }
    /* Possible weaknesses found:
     *  use of uninitialized value 'data' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    return data;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    struct Node* head = NULL;
    for(int i = 0; i < n; i++) {
        addNode(&head, arr[i]);
    }
    printf("The item with maximum frequency is %d\n", findMaxFreq(head));
    return 0;
}