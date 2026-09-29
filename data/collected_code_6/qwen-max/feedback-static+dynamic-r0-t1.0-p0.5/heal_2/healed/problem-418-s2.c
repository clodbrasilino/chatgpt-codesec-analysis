#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int lengthOfList(Node *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

Node* findMaxSublist(Node *head1, Node *head2) {
    int len1 = lengthOfList(head1);
    int len2 = lengthOfList(head2);
    return (len1 > len2) ? head1 : head2;
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *list1 = NULL;
    Node *list2 = NULL;

    insertNode(&list1, 1);
    insertNode(&list1, 2);
    insertNode(&list1, 3);

    insertNode(&list2, 4);
    insertNode(&list2, 5);
    insertNode(&list2, 6);
    insertNode(&list2, 7);

    Node *maxSublist = findMaxSublist(list1, list2);

    printf("List 1: ");
    printList(list1);
    printf("List 2: ");
    printList(list2);
    printf("Max Sublist: ");
    printList(maxSublist);

    freeList(list1);
    freeList(list2);

    return 0;
}