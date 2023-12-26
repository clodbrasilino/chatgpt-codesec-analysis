#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node with given data
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to calculate the difference between two lists
int getDifference(Node* list1, Node* list2) {
    int sum1 = 0, sum2 = 0;
    while (list1 != NULL) {
        sum1 += list1->data;
        list1 = list1->next;
    }
    while (list2 != NULL) {
        sum2 += list2->data;
        list2 = list2->next;
    }
    return abs(sum1 - sum2);
}

// Driver program to test above functions
int main() {
    Node* list1 = newNode(3);
    list1->next = newNode(5);
    list1->next->next = newNode(8);

    Node* list2 = newNode(1);
    list2->next = newNode(2);

    int difference = getDifference(list1, list2);
    printf("Difference between the two lists is: %d\n", difference);

    return 0;
}
