#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListList {
    Node* head;
    struct ListList* next;
} ListList;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

ListList* createListList(Node* head) {
    ListList* newLL = (ListList*)malloc(sizeof(ListList));
    if (!newLL) {
        exit(EXIT_FAILURE);
    }
    newLL->head = head;
    newLL->next = NULL;
    return newLL;
}

ListList* splitList(Node* head, int n) {
    if (!head || n <= 0) {
        return NULL;
    }

    ListList* resultHead = NULL;
    ListList* currentLL = NULL;
    Node* current = head;

    while (current) {
        Node* currPartHead = NULL;
        Node* currPartTail = NULL;
        
        for (int i = 0; i < n && current != NULL; i++) {
            Node* newNode = createNode(current->data);
            if (!currPartHead) {
                currPartHead = newNode;
                currPartTail = newNode;
            } else {
                currPartTail->next = newNode;
                currPartTail = newNode;
            }
            current = current->next;
        }

        ListList* newLL = createListList(currPartHead);
        if (!resultHead) {
            resultHead = newLL;
            currentLL = newLL;
        } else {
            currentLL->next = newLL;
            currentLL = newLL;
        }
    }

    return resultHead;
}

void printAndFreeResult(ListList* ll) {
    ListList* currLL = ll;
    while (currLL) {
        Node* currNode = currLL->head;
        printf("[ ");
        while (currNode) {
            printf("%d ", currNode->data);
            Node* tempNode = currNode;
            currNode = currNode->next;
            free(tempNode);
        }
        printf("]\n");
        ListList* tempLL = currLL;
        currLL = currLL->next;
        free(tempLL);
    }
}

void freeOriginalList(Node* head) {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 1; i <= 10; i++) {
        Node* newNode = createNode(i);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    int n = 3;
    ListList* split = splitList(head, n);

    printAndFreeResult(split);
    freeOriginalList(head);

    return 0;
}