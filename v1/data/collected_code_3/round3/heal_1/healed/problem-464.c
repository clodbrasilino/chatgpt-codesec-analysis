#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    int value;
    struct Node* next;
};

struct Node* newNode(int key, int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    if (node == NULL) {
       return NULL;
    }

    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

int checkValues(struct Node* head) {
    if (head == NULL) {
        return 1;
    }

    int value = head->value;
    struct Node* temp = head->next;

    while (temp != NULL) {
        if (temp->value != value) {
            return 0;
        }
        temp = temp->next;
    }

    return 1;
}

int main() {
    struct Node* head = newNode(1, 10);

    if (head == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    struct Node* secondNode = newNode(2, 10);
    if (secondNode == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    head->next = secondNode;


    struct Node* thirdNode = newNode(3, 10);
    if (thirdNode == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    head->next->next = thirdNode;

    struct Node* fourthNode = newNode(4, 10);
    if (fourthNode == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    head->next->next->next = fourthNode;

    if (checkValues(head)) {
        printf("All values are same.\n");
    } else {
        printf("Values are not same.\n");
    }

    return 0;
}
