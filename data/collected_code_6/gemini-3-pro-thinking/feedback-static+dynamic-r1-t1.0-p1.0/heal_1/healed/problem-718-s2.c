#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data);
int appendNode(struct Node** head, int data);
void freeList(struct Node* head);
struct Node* alternateList(const struct Node* head);
void printList(const struct Node* head);

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

int appendNode(struct Node** head, int data) {
    if (head == NULL) {
        return 0;
    }
    
    struct Node* newNode = createNode(data);
    if (newNode == NULL) {
        return 0;
    }

    if (*head == NULL) {
        *head = newNode;
        return 1;
    }

    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return 1;
}

void freeList(struct Node* head) {
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
}

struct Node* alternateList(const struct Node* head) {
    struct Node* newHead = NULL;
    struct Node** currentNew = &newHead;
    const struct Node* currentOriginal = head;
    int toggle = 1;

    while (currentOriginal != NULL) {
        if (toggle) {
            *currentNew = createNode(currentOriginal->data);
            if (*currentNew == NULL) {
                freeList(newHead);
                return NULL;
            }
            currentNew = &((*currentNew)->next);
        }
        toggle = !toggle;
        currentOriginal = currentOriginal->next;
    }
    return newHead;
}

void printList(const struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    struct Node* originalList = NULL;
    struct Node* altList = NULL;

    for (int i = 1; i <= 10; ++i) {
        if (!appendNode(&originalList, i)) {
            freeList(originalList);
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    if (originalList != NULL) {
        altList = alternateList(originalList);
        if (altList == NULL) {
            freeList(originalList);
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    printList(originalList);
    printList(altList);

    freeList(originalList);
    freeList(altList);

    return EXIT_SUCCESS;
}