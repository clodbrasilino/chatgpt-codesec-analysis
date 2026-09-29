#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListArray {
    Node** lists;
    int count;
} ListArray;

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

void freeListArray(ListArray* array) {
    if (!array) return;
    
    if (array->lists) {
        for (int i = 0; i < array->count; i++) {
            freeList(array->lists[i]);
        }
        free(array->lists);
    }
    free(array);
}

void printList(Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

ListArray* splitList(Node* head, int n) {
    if (n <= 0) {
        return NULL;
    }

    ListArray* result = (ListArray*)malloc(sizeof(ListArray));
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int length = 0;
    Node* temp = head;
    while (temp) {
        length++;
        temp = temp->next;
    }

    if (length == 0) {
        result->count = 0;
        result->lists = NULL;
        return result;
    }

    result->count = (length + n - 1) / n;
    result->lists = (Node**)malloc(result->count * sizeof(Node*));
    if (!result->lists) {
        fprintf(stderr, "Memory allocation failed\n");
        free(result);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < result->count; i++) {
        result->lists[i] = NULL;
    }

    temp = head;
    for (int i = 0; i < result->count; i++) {
        for (int j = 0; j < n && temp; j++) {
            appendNode(&(result->lists[i]), temp->data);
            temp = temp->next;
        }
    }

    return result;
}

int main(void) {
    Node* head = NULL;
    for (int i = 1; i <= 10; i++) {
        appendNode(&head, i);
    }

    printf("Original List:\n");
    printList(head);

    int n = 3;
    printf("\nSplitting every %d elements:\n", n);
    ListArray* splitResult = splitList(head, n);

    if (splitResult) {
        for (int i = 0; i < splitResult->count; i++) {
            printf("List %d: ", i + 1);
            printList(splitResult->lists[i]);
        }
        freeListArray(splitResult);
    }

    freeList(head);
    return 0;
}