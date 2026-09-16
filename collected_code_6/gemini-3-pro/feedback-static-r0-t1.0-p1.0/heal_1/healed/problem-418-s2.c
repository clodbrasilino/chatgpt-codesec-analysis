#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int data) {
    if (!head) {
        return;
    }
    Node* newNode = createNode(data);
    if (!newNode) {
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

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

const Node* findGivenSublist(Node** lists, int numLists, int* maxLength) {
    if (!lists || numLists <= 0 || !maxLength) {
        return NULL;
    }

    const Node* maxList = NULL;
    *maxLength = 0;

    for (int i = 0; i < numLists; i++) {
        Node* current = lists[i];
        int count = 0;
        
        while (current != NULL) {
            count++;
            current = current->next;
        }
        
        if (count > *maxLength) {
            *maxLength = count;
            maxList = lists[i];
        }
    }

    return maxList;
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* list3 = NULL;

    append(&list1, 1);
    append(&list1, 2);
    
    append(&list2, 1);
    append(&list2, 2);
    append(&list2, 3);
    append(&list2, 4);
    
    append(&list3, 1);
    append(&list3, 2);
    append(&list3, 3);

    Node* lists[] = {list1, list2, list3};
    int numLists = sizeof(lists) / sizeof(lists[0]);
    int maxLength = 0;

    const Node* maxList = findGivenSublist(lists, numLists, &maxLength);

    if (maxList) {
        printf("%d\n", maxLength);
    } else {
        printf("0\n");
    }

    freeList(list1);
    freeList(list2);
    freeList(list3);

    return 0;
}