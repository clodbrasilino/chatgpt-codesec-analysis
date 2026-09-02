#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
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

Node* addLists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node* current1 = list1;
    Node* current2 = list2;
    int carry = 0;
    Node* dummyHead = createNode(0);
    Node* current = dummyHead;

    while (current1 || current2 || carry) {
        int sum = (current1 ? current1->data : 0) + (current2 ? current2->data : 0) + carry;
        carry = sum / 10;
        appendNode(&result, sum % 10);

        if (current1) current1 = current1->next;
        if (current2) current2 = current2->next;
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

    appendNode(&list1, 9);
    appendNode(&list1, 9);
    appendNode(&list1, 9);

    appendNode(&list2, 1);
    appendNode(&list2, 0);
    appendNode(&list2, 0);
    appendNode(&list2, 1);

    Node* result = addLists(list1, list2);
    printList(result);

    return 0;
}