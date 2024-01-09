#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, int value) {
    if (*head == NULL) {
        *head = createNode(value);
    } else {
        Node* curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = createNode(value);
    }
}

void displayList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

Node* convertToList(int* arr, int size) {
    Node* head = NULL;
    for (int i = 0; i < size; i++) {
        insertNode(&head, arr[i]);
    }
    return head;
}

void convertToTuple(Node* head, int** tuple, int* size) {
    Node* curr = head;
    *size = 0;
    while (curr != NULL) {
        (*size)++;
        curr = curr->next;
    }
    *tuple = (int*)malloc(*size * sizeof(int));
    curr = head;
    for (int i = 0; i < *size; i++) {
        (*tuple)[i] = curr->data;
        curr = curr->next;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    Node* head = convertToList(arr, size);

    int* tuple;
    int tupleSize;
    convertToTuple(head, &tuple, &tupleSize);

    printf("Tuple: ");
    for (int i = 0; i < tupleSize; i++) {
        printf("%d ", tuple[i]);
    }
    printf("\n");

    free(tuple);
    return 0;
}