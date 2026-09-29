#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) exit(EXIT_FAILURE);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

List* createList(Node* head) {
    List* newList = (List*)malloc(sizeof(List));
    if (!newList) exit(EXIT_FAILURE);
    newList->head = head;
    newList->next = NULL;
    return newList;
}

void freeNodeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void freeList(List* head) {
    List* current = head;
    while (current != NULL) {
        List* temp = current;
        current = current->next;
        freeNodeList(temp->head);
        free(temp);
    }
}

List* removeSublistsOutsideRange(List* head, int min_val, int max_val) {
    List* current = head;
    List* prev = NULL;

    while (current != NULL) {
        int in_range = 1;
        Node* node = current->head;
        while (node != NULL) {
            if (node->value < min_val || node->value > max_val) {
                in_range = 0;
                break;
            }
            node = node->next;
        }

        if (!in_range) {
            List* temp = current;
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            freeNodeList(temp->head);
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }

    return head;
}

void printList(List* head) {
    List* current = head;
    while (current != NULL) {
        Node* node = current->head;
        printf("[");
        while (node != NULL) {
            printf("%d", node->value);
            if (node->next != NULL) printf(", ");
            node = node->next;
        }
        printf("]");
        if (current->next != NULL) printf(" -> ");
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* n1 = createNode(1);
    n1->next = createNode(2);
    n1->next->next = createNode(3);

    Node* n2 = createNode(4);
    n2->next = createNode(5);
    n2->next->next = createNode(6);

    Node* n3 = createNode(7);
    n3->next = createNode(8);
    n3->next->next = createNode(9);

    List* l1 = createList(n1);
    List* l2 = createList(n2);
    List* l3 = createList(n3);

    l1->next = l2;
    l2->next = l3;

    List* result = removeSublistsOutsideRange(l1, 3, 6);

    printList(result);

    freeList(result);

    return 0;
}