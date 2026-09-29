#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct ListNode {
    int data;
    struct ListNode* next;
} Node;

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'temp' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    temp->data = data;
    temp->next = NULL;
    return temp;
}

int findMinLengthList(Node** head, int n) {
    int minLength = INT_MAX;
    for (int i = 0; i < n; i++) {
        Node *ptr = head[i];
        int count = 0;
        while (ptr != NULL) {
            count++;
            ptr = ptr->next;
        }
        if (count < minLength) {
            minLength = count;
        }
    }
    return minLength;
}

int main() {
    int n = 4;
    Node* head[n];

    head[0] = newNode(1);
    head[0]->next = newNode(2);
    head[0]->next->next = newNode(3);

    head[1] = newNode(1);
    head[1]->next = newNode(2);

    head[2] = newNode(1);

    head[3] = newNode(1);
    head[3]->next = newNode(2);
    head[3]->next->next = newNode(3);
    head[3]->next->next->next = newNode(4);

    int res = findMinLengthList(head, n);
    printf("The minimum length list length is: %d\n", res);
    return 0;
}