#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct NodeList {
    struct Node* head;
    struct NodeList* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct NodeList* createNodeList(struct Node* head) {
    struct NodeList* newList = (struct NodeList*)malloc(sizeof(struct NodeList));
    if (!newList) {
        return NULL;
    }
    newList->head = head;
    newList->next = NULL;
    return newList;
}

struct NodeList* splitList(struct Node* head, int n) {
    if (!head || n <= 0) {
        return NULL;
    }

    struct NodeList* resultHead = NULL;
    struct NodeList* resultTail = NULL;
    struct Node* current = head;

    while (current) {
        struct Node* partHead = current;
        struct Node* partTail = current;
        int count = 1;

        while (count < n && partTail->next) {
            partTail = partTail->next;
            count++;
        }

        current = partTail->next;
        partTail->next = NULL;

        struct NodeList* newList = createNodeList(partHead);
        if (!newList) {
            while (resultHead) {
                struct NodeList* tmp = resultHead;
                resultHead = resultHead->next;
                free(tmp);
            }
            return NULL;
        }

        if (!resultHead) {
            resultHead = newList;
            resultTail = newList;
        } else {
            resultTail->next = newList;
            resultTail = newList;
        }
    }

    return resultHead;
}

void printAndFreeResult(struct NodeList* result) {
    struct NodeList* currentList = result;
    while (currentList) {
        struct Node* current = currentList->head;
        while (current) {
            printf("%d ", current->data);
            struct Node* tmp = current;
            current = current->next;
            free(tmp);
        }
        printf("\n");
        struct NodeList* tmpList = currentList;
        currentList = currentList->next;
        free(tmpList);
    }
}

int main() {
    struct Node* head = createNode(1);
    if (!head) return 1;
    
    struct Node* current = head;
    for (int i = 2; i <= 10; ++i) {
        current->next = createNode(i);
        if (!current->next) {
            struct Node* tmp = head;
            while (tmp) {
                struct Node* next = tmp->next;
                free(tmp);
                tmp = next;
            }
            return 1;
        }
        current = current->next;
    }

    struct NodeList* result = splitList(head, 3);
    
    if (result) {
        printAndFreeResult(result);
    } else {
        while (head) {
            struct Node* tmp = head;
            head = head->next;
            free(tmp);
        }
    }

    return 0;
}