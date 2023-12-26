#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

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

int main() {
    Node* list1 = newNode(3);
    if(list1 == NULL) {
        return -1;
    }
    list1->next = newNode(5);
    if(list1->next == NULL) {
        free(list1);
        return -1;
    }
    list1->next->next = newNode(8);
    if(list1->next->next == NULL) {
        free(list1->next);
        free(list1);
        return -1;
    }

    Node* list2 = newNode(1);
    if(list2 == NULL) {
        free(list1->next->next);
        free(list1->next);
        free(list1);
        return -1;
    }
    list2->next = newNode(2);
    if(list2->next == NULL) {
        free(list1->next->next);
        free(list1->next);
        free(list1);
        free(list2);
        return -1;
    }

    int difference = getDifference(list1, list2);
    printf("Difference between the two lists is: %d\n", difference);

    free(list1->next->next);
    free(list1->next);
    free(list1);
    free(list2->next);
    free(list2);

    return 0;
}