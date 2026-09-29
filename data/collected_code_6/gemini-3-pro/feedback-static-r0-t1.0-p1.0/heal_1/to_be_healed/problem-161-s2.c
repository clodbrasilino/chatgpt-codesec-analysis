#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int data) {
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

    while (*list1 && isPresent(list2, (*list1)->data)) {
        Node* temp = *list1;
        *list1 = (*list1)->next;
        free(temp);
    }

    Node* current = *list1;
    while (current && current->next) {
        if (isPresent(list2, current->next->data)) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
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

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;

    append(&list1, 1);
    append(&list1, 2);
    append(&list1, 3);
    append(&list1, 4);
    append(&list1, 5);

    append(&list2, 2);
    append(&list2, 4);
    append(&list2, 6);

    removeElements(&list1, list2);

    printList(list1);

    freeList(list1);
    freeList(list2);

    return 0;
}