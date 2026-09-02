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

void insertAtEnd(Node **head, int data) {
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

void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void removeElements(Node **list1, Node *list2) {
    Node *current1 = *list1;
    Node *prev1 = NULL;
    while (current1 != NULL) {
        Node *current2 = list2;
        while (current2 != NULL) {
            if (current1->data == current2->data) {
                Node *toDelete = current1;
                if (prev1 == NULL) {
                    *list1 = current1->next;
                } else {
                    prev1->next = current1->next;
                }
                free(toDelete);
                current1 = prev1 ? prev1->next : *list1;
                break;
            }
            current2 = current2->next;
        }
        if (current2 == NULL) {
            prev1 = current1;
            current1 = current1->next;
        }
    }
}

int main() {
    Node *list1 = NULL;
    Node *list2 = NULL;

    insertAtEnd(&list1, 10);
    insertAtEnd(&list1, 20);
    insertAtEnd(&list1, 30);
    insertAtEnd(&list1, 40);
    insertAtEnd(&list1, 50);

    insertAtEnd(&list2, 20);
    insertAtEnd(&list2, 40);

    printf("List1 before removal: ");
    printList(list1);

    printf("List2: ");
    printList(list2);

    removeElements(&list1, list2);

    printf("List1 after removal: ");
    printList(list1);

    return 0;
}