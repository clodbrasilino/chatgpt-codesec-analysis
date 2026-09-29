#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data);
void appendNode(Node** head, int data);
Node* mergeLists(Node* list1, Node* list2);
void printList(const Node* head);
void freeList(Node* head);

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
    if (head == NULL) {
        return;
    }
    
    Node* newNode = createNode(data);
    
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

Node* mergeLists(Node* list1, Node* list2) {
    Node dummy;
    dummy.data = 0;
    dummy.next = NULL;
    Node* tail = &dummy;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != NULL) {
        tail->next = list1;
    } else if (list2 != NULL) {
        tail->next = list2;
    }

    return dummy.next;
}

void printList(const Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* mergedList = NULL;

    appendNode(&list1, 1);
    appendNode(&list1, 3);
    appendNode(&list1, 5);
    appendNode(&list1, 7);

    appendNode(&list2, 2);
    appendNode(&list2, 4);
    appendNode(&list2, 6);
    appendNode(&list2, 8);

    mergedList = mergeLists(list1, list2);

    printList(mergedList);

    freeList(mergedList);

    return EXIT_SUCCESS;
}