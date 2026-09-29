#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int first;
    int second;
    struct Node* next;
} Node;

Node* createNode(int first, int second) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->first = first;
    newNode->second = second;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node** head, int first, int second) {
    if (!head) return;
    
    Node* newNode = createNode(first, second);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printList(Node* head) {
    while (head != NULL) {
        printf("[%d, %d] ", head->first, head->second);
        head = head->next;
    }
    printf("\n");
}

void bubbleSort(Node* head) {
    if (!head) return;

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->second > ptr1->next->second) {
                int tempFirst = ptr1->first;
                int tempSecond = ptr1->second;
                
                ptr1->first = ptr1->next->first;
                ptr1->second = ptr1->next->second;
                
                ptr1->next->first = tempFirst;
                ptr1->next->second = tempSecond;
                
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int main(void) {
    Node* head = NULL;

    insertAtEnd(&head, 1, 4);
    insertAtEnd(&head, 3, 1);
    insertAtEnd(&head, 2, 8);
    insertAtEnd(&head, 5, 2);

    printList(head);

    bubbleSort(head);

    printList(head);

    freeList(head);

    return EXIT_SUCCESS;
}