#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int listLength(Node *head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

Node* findLongestList(Node *list1, Node *list2) {
    int len1 = listLength(list1);
    int len2 = listLength(list2);
    return (len1 >= len2) ? list1 : list2;
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node *list1 = createNode(1);
    list1->next = createNode(2);
    list1->next->next = createNode(3);

    Node *list2 = createNode(4);
    list2->next = createNode(5);

    Node *longestList = findLongestList(list1, list2);

    printf("List 1: ");
    printList(list1);
    printf("List 2: ");
    printList(list2);
    printf("Longest List: ");
    printList(longestList);

    return 0;
}