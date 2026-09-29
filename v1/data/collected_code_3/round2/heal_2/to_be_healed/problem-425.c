#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

int countSublists(struct Node* start, int x) {
    struct Node* current = start;
    int count = 0;
    while (current != NULL) {
        if (current->data == x) {
            count++;
        }
        current = current->next;
    }
    return count;
}

int main() {
    struct Node* start = newNode(1);
    if (start != NULL) {
        start->next = newNode(2);
        if (start->next != NULL) {
            start->next->next = newNode(1);
        }
        /* Possible weaknesses found:
         *  dereference of NULL '*start.next' [CWE-476] [-Wanalyzer-null-dereference]
         *  use of uninitialized value '*start_23->next.next' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        if (start->next->next != NULL) {
            start->next->next->next = newNode(3);
        }
        /* Possible weaknesses found:
         *  use of uninitialized value '*_10->next.next' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  dereference of NULL '*start_23->next.next' [CWE-476] [-Wanalyzer-null-dereference]
         */
        if (start->next->next->next != NULL) {
            start->next->next->next->next = newNode(1);
        }
    }

    printf("Count of sublists containing 1 is %d", countSublists(start, 1));

    return 0;
}