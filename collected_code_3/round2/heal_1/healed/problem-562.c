#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int count;
    struct Node* next;
};

int max(int a, int b) {
    return (a > b)? a : b;
}

int maxLen(struct Node *head) {
    int max_len = 0;
    struct Node *prev = NULL, *curr = head;

    while (curr != NULL) {
        prev = curr;
        while (curr != NULL && prev->data == curr->data) {
            curr = curr->next;
            prev->count += 1;
        }
        max_len = max(max_len, prev->count);
        if (curr != NULL) {
            curr->count = 1;
        }
    }
    return max_len;
}

struct Node* newNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode != NULL) {
        newNode->data = data;
        newNode->count = 1;
        newNode->next = NULL;
    }

    return newNode;
}

int main() {
    struct Node* head = newNode(1);
    if (head != NULL) {
        head->next = newNode(1);
        if (head->next != NULL) {
            head->next->next = newNode(2);
            if (head->next->next != NULL) {
                head->next->next->next = newNode(2);
                if (head->next->next->next != NULL) {
                    head->next->next->next->next = newNode(2);
                    if (head->next->next->next->next != NULL) {
                        head->next->next->next->next->next = newNode(3);
                        if (head->next->next->next->next->next != NULL) {
                            head->next->next->next->next->next->next = newNode(3);
                        }
                    }
                }
            }
        }
    }
    printf("%d", maxLen(head));
    return 0;
}