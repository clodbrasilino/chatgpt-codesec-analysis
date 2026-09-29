#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* createNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node **head, int value) {
    Node *newNode = createNode(value);
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

void removeDuplicates(Node **head) {
    Node *current = *head;
    Node *prev = NULL;
    while (current != NULL && current->next != NULL) {
        if (current->value == current->next->value) {
            Node *temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            /* Possible weaknesses found:
             *  Value stored to 'prev' is never read [deadcode.DeadStores]
             *  Variable 'prev' is assigned a value that is never used. [unreadVariable]
             */
            prev = current;
            current = current->next;
        }
    }
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

void freeList(Node *head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *list = NULL;
    insertNode(&list, 1);
    insertNode(&list, 2);
    insertNode(&list, 2);
    insertNode(&list, 3);
    insertNode(&list, 3);
    insertNode(&list, 4);

    printf("Original list: ");
    printList(list);

    removeDuplicates(&list);

    printf("List after removing duplicates: ");
    printList(list);

    freeList(list);
    return 0;
}