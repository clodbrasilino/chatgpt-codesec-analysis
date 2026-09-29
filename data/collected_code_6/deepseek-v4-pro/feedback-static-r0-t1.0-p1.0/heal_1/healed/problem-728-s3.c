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

void freeList(Node* head);

Node* createList(const int* arr, int size) {
    if (size <= 0 || arr == NULL) {
        return NULL;
    }
    
    Node* head = createNode(arr[0]);
    if (head == NULL) {
        return NULL;
    }
    
    Node* current = head;
    for (int i = 1; i < size; i++) {
        current->next = createNode(arr[i]);
        if (current->next == NULL) {
            freeList(head);
            return NULL;
        }
        current = current->next;
    }
    return head;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int sumList(Node* head) {
    int sum = 0;
    Node* current = head;
    while (current != NULL) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}

int sumTwoLists(Node* list1, Node* list2) {
    return sumList(list1) + sumList(list2);
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, 20, 30};
    
    Node* list1 = createList(arr1, 5);
    Node* list2 = createList(arr2, 3);
    
    if (list1 == NULL || list2 == NULL) {
        if (list1 != NULL) freeList(list1);
        if (list2 != NULL) freeList(list2);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    int total = sumTwoLists(list1, list2);
    printf("Sum of both lists: %d\n", total);
    
    freeList(list1);
    freeList(list2);
    
    return EXIT_SUCCESS;
}