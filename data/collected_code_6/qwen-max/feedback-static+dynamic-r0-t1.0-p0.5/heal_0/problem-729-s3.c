#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addToList(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

Node* addTwoLists(Node* first, Node* second) {
    Node* result = NULL;
    int carry = 0;
    while (first != NULL || second != NULL || carry) {
        int sum = (first ? first->data : 0) + (second ? second->data : 0) + carry;
        carry = sum / 10;
        sum = sum % 10;
        addToList(&result, sum);
        if (first) first = first->next;
        if (second) second = second->next;
    }
    return result;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;

    addToList(&list1, 7);
    addToList(&list1, 3);
    addToList(&list1, 9);

    addToList(&list2, 8);
    addToList(&list2, 4);
    addToList(&list2, 6);

    Node* result = addTwoLists(list1, list2);

    printList(result);

    return 0;
}