#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data);
void freeList(struct Node* head);
struct Node* getAlternateList(const struct Node* head);
void printList(const struct Node* head);

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

struct Node* getAlternateList(const struct Node* head) {
    if (!head) {
        return NULL;
    }

    struct Node* newHead = NULL;
    struct Node* currentNew = NULL;
    const struct Node* currentOld = head;
    int take = 1;

    while (currentOld != NULL) {
        if (take) {
            struct Node* newNode = createNode(currentOld->data);
            if (!newNode) {
                freeList(newHead);
                return NULL;
            }

            if (!newHead) {
                newHead = newNode;
                currentNew = newHead;
            } else {
                currentNew->next = newNode;
                currentNew = currentNew->next;
            }
        }
        take = !take;
        currentOld = currentOld->next;
    }

    return newHead;
}

void printList(const struct Node* head) {
    const struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    struct Node* head = NULL;
    struct Node* tail = NULL;

    for (int i = 1; i <= 10; i++) {
        struct Node* newNode = createNode(i);
        if (!newNode) {
            freeList(head);
            return EXIT_FAILURE;
        }
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = tail->next;
        }
    }

    struct Node* altList = getAlternateList(head);
    if (!altList && head != NULL) {
        freeList(head);
        return EXIT_FAILURE;
    }

    printList(head);
    printList(altList);

    freeList(head);
    freeList(altList);

    return EXIT_SUCCESS;
}