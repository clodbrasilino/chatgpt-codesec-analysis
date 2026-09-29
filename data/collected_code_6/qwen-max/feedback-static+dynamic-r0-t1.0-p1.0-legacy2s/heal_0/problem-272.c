#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

Node* createNode(Tuple data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, Tuple data) {
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

Tuple extractRear(Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        Tuple empty = {0, 0};
        return empty;
    }

    Node* current = *head;
    Node* prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    Tuple rearData = current->data;
    free(current);
    if (prev != NULL) {
        prev->next = NULL;
    }
    return rearData;
}

int main() {
    Node* head = NULL;

    Tuple data1 = {1, 10};
    Tuple data2 = {2, 20};
    Tuple data3 = {3, 30};

    appendNode(&head, data1);
    appendNode(&head, data2);
    appendNode(&head, data3);

    Tuple rear = extractRear(&head);
    printf("Rear element: Key = %d, Value = %d\n", rear.key, rear.value);

    return 0;
}