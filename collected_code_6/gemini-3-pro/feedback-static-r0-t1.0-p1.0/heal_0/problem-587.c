#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode* next;
};

struct Tuple {
    int* elements;
    size_t size;
};

struct Tuple convertListToTuple(struct ListNode* head) {
    struct Tuple tuple = {NULL, 0};
    struct ListNode* current = head;
    size_t count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    if (count == 0) {
        return tuple;
    }

    tuple.elements = (int*)malloc(count * sizeof(int));
    if (tuple.elements == NULL) {
        return tuple;
    }

    tuple.size = count;
    current = head;
    size_t i = 0;
    while (current != NULL) {
        tuple.elements[i] = current->data;
        current = current->next;
        i++;
    }

    return tuple;
}

void freeTuple(struct Tuple* tuple) {
    if (tuple != NULL && tuple->elements != NULL) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

void freeList(struct ListNode* head) {
    struct ListNode* current = head;
    struct ListNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

struct ListNode* createNode(int data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

int main(void) {
    struct ListNode* head = createNode(1);
    if (head == NULL) return 1;
    head->next = createNode(2);
    if (head->next == NULL) {
        freeList(head);
        return 1;
    }
    head->next->next = createNode(3);
    if (head->next->next == NULL) {
        freeList(head);
        return 1;
    }

    struct Tuple t = convertListToTuple(head);

    if (t.elements != NULL) {
        for (size_t i = 0; i < t.size; i++) {
            printf("%d ", t.elements[i]);
        }
        printf("\n");
        freeTuple(&t);
    }

    freeList(head);

    return 0;
}