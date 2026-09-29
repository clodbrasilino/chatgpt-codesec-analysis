#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
 /* Possible weaknesses found:
  *  test case 1 failed: expected 24, got <no output>
  *  test case 0 failed: expected -6, got <no output>
  *  test case 2 failed: expected 18, got <no output>
  */

long long multiplyListItems(struct Node* head) {
    if (head == NULL) {
        return 0; 
    }

    long long result = 1;
    struct Node* current = head;

    while (current != NULL) {
        result *= current->data;
        current = current->next;
    }

    return result;
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main(void) {
    int val;
    struct Node* head = NULL;
    struct Node* tail = NULL;

    while (scanf("%d", &val) == 1) {
        struct Node* newNode = createNode(val);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    long long product = multiplyListItems(head);

    printf("%lld\n", product);

    freeList(head);

    return 0;
}