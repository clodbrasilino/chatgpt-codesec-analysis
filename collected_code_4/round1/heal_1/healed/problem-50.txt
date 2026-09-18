#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct ListNode {
    int data;
    struct ListNode* next;
} Node;

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));

    if(temp != NULL) {
        temp->data = data;
        temp->next = NULL;
    }
    
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
    if(head[0] != NULL) {
        head[0]->next = newNode(2); 
        if(head[0]->next != NULL) 
            head[0]->next->next = newNode(3);
    }

    head[1] = newNode(1);
    if(head[1] != NULL)
        head[1]->next = newNode(2);

    head[2] = newNode(1);

    head[3] = newNode(1);
    if(head[3] != NULL) {
        head[3]->next = newNode(2); 
        if(head[3]->next != NULL) {
            head[3]->next->next = newNode(3);
            if(head[3]->next->next != NULL)
                head[3]->next->next->next = newNode(4);
        }
    }
    
    int res = findMinLengthList(head, n);
    printf("The minimum length list length is: %d\n", res + 1);

    for(int i=0; i<n; i++) {
        Node *ptr;
        while((ptr = head[i]) != NULL) {
            head[i] = head[i]->next;
            free(ptr);
        }
    }

    return 0;
}