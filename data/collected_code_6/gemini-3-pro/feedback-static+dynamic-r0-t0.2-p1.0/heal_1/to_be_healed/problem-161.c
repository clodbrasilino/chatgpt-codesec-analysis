#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    if (!head) return;
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int isPresent(Node* head, int data) {
    Node* temp = head;
    while (temp) {
        if (temp->data == data) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void removeElements(Node** list1, Node* list2) {
    if (!list1 || !*list1 || !list2) return;

    Node* current = *list1;
    Node* prev = NULL;

    while (current) {
        if (isPresent(list2, current->data)) {
            Node* temp = current;
            if (prev) {
                prev->next = current->next;
            } else {
                *list1 = current->next;
            }
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;

    appendNode(&list1, 1);
    appendNode(&list1, 2);
    appendNode(&list1, 3);
    appendNode(&list1, 4);
    appendNode(&list1, 5);

    appendNode(&list2, 2);
    appendNode(&list2, 4);
    appendNode(&list2, 6);

    removeElements(&list1, list2);

    printList(list1);

    freeList(list1);
    freeList(list2);

    return 0;
}