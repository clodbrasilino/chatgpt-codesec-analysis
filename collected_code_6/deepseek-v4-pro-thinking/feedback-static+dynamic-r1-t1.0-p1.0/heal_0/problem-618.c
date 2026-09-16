#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *createNode(int data) {
    Node *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int appendNode(Node **head, int data) {
    if (head == NULL) {
        return 0;
    }

    Node *newNode = createNode(data);
    if (newNode == NULL) {
        return 0;
    }

    if (*head == NULL) {
        *head = newNode;
        return 1;
    }

    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    return 1;
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int divideLists(const Node *list1, const Node *list2, Node **result) {
    if (result == NULL) {
        fprintf(stderr, "Error: Invalid output parameter\n");
        return -1;
    }

    Node *newList = NULL;
    Node **tail = &newList;
    *result = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list2->data == 0) {
            fprintf(stderr, "Error: Division by zero\n");
            freeList(newList);
            return -1;
        }

        Node *newNode = createNode(list1->data / list2->data);
        if (newNode == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            freeList(newList);
            return -1;
        }

        *tail = newNode;
        tail = &newNode->next;

        list1 = list1->next;
        list2 = list2->next;
    }

    if (list1 != NULL || list2 != NULL) {
        fprintf(stderr, "Error: Lists have different lengths\n");
        freeList(newList);
        return -1;
    }

    *result = newList;
    return 0;
}

void printList(const Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;
    Node *result = NULL;

    if (!appendNode(&list1, 10) || !appendNode(&list1, 20) || !appendNode(&list1, 30)) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        freeList(list1);
        return EXIT_FAILURE;
    }

    if (!appendNode(&list2, 2) || !appendNode(&list2, 4) || !appendNode(&list2, 5)) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        freeList(list1);
        freeList(list2);
        return EXIT_FAILURE;
    }

    if (divideLists(list1, list2, &result) != 0) {
        freeList(list1);
        freeList(list2);
        return EXIT_FAILURE;
    }

    printList(result);

    freeList(result);
    freeList(list1);
    freeList(list2);

    return EXIT_SUCCESS;
}