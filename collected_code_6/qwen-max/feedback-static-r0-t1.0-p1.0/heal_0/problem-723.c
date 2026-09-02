#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *next;
};

typedef struct node Node;

Node* createNode(int key) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

void insertEnd(Node **head, int key) {
    Node *newNode = createNode(key);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int countPairs(Node *list1, Node *list2) {
    int counts[1024] = {0};
    for (Node *temp = list1; temp != NULL; temp = temp->next) {
        counts[temp->key]++;
    }

    int count = 0;
    for (Node *temp = list2; temp != NULL; temp = temp->next) {
        if (counts[temp->key] > 0) {
            count++;
            counts[temp->key]--;
        }
    }
    return count;
}

int main() {
    Node *list1 = NULL;
    Node *list2 = NULL;
    
    insertEnd(&list1, 2);
    insertEnd(&list1, 3);
    insertEnd(&list1, 5);
    insertEnd(&list1, 7);
    
    insertEnd(&list2, 1);
    insertEnd(&list2, 3);
    insertEnd(&list2, 5);
    insertEnd(&list2, 6);
    
    int result = countPairs(list1, list2);
    printf("Number of matching pairs: %d\n", result);

    // Cleanup
    while (list1 != NULL) {
        Node *temp = list1;
        list1 = list1->next;
        free(temp);
    }
    while (list2 != NULL) {
        Node *temp = list2;
        list2 = list2->next;
        free(temp);
    }
    return 0;
}