#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head_ref, int new_data) {
    struct Node* newNode = createNode(new_data);
    struct Node* last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

void freeList(struct Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int sumLists(struct Node* list1, struct Node* list2) {
    int sum = 0;
    while (list1 != NULL) {
        sum += list1->data;
        list1 = list1->next;
    }
    while (list2 != NULL) {
        sum += list2->data;
        list2 = list2->next;
    }
    return sum;
}

int main(void) {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    appendNode(&list1, 1);
    appendNode(&list1, 2);
    appendNode(&list1, 3);

    appendNode(&list2, 4);
    appendNode(&list2, 5);
    appendNode(&list2, 6);

    int totalSum = sumLists(list1, list2);
    printf("Sum: %d\n", totalSum);

    freeList(list1);
    freeList(list2);

    return 0;
}