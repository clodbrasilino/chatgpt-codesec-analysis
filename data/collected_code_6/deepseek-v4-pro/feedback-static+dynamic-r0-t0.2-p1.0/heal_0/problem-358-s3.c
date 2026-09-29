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

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

int listLength(Node* head) {
    int length = 0;
    Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

int listToNumber(Node* head) {
    int number = 0;
    Node* current = head;
    while (current != NULL) {
        number = number * 10 + current->data;
        current = current->next;
    }
    return number;
}

Node* numberToList(int number) {
    Node* head = NULL;
    if (number == 0) {
        appendNode(&head, 0);
        return head;
    }
    int digits[32];
    int count = 0;
    while (number > 0) {
        digits[count++] = number % 10;
        number /= 10;
    }
    for (int i = count - 1; i >= 0; i--) {
        appendNode(&head, digits[i]);
    }
    return head;
}

Node* moduloDivision(Node* list1, Node* list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }
    int num1 = listToNumber(list1);
    int num2 = listToNumber(list2);
    if (num2 == 0) {
        return NULL;
    }
    int result = num1 % num2;
    return numberToList(result);
}

void printList(Node* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    
    appendNode(&list1, 1);
    appendNode(&list1, 2);
    appendNode(&list1, 3);
    
    appendNode(&list2, 1);
    appendNode(&list2, 0);
    
    printf("List 1: ");
    printList(list1);
    printf("List 2: ");
    printList(list2);
    
    Node* result = moduloDivision(list1, list2);
    printf("Modulo result: ");
    printList(result);
    
    freeList(list1);
    freeList(list2);
    freeList(result);
    
    return 0;
}