#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(struct Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

struct Node* divideLists(struct Node* list1, struct Node* list2) {
    struct Node* resultHead = NULL;
    struct Node* current1 = list1;
    struct Node* current2 = list2;

    while (current1 != NULL && current2 != NULL) {
        if (current2->data == 0) {
            freeList(resultHead);
            return NULL;
        }
        append(&resultHead, current1->data / current2->data);
        current1 = current1->next;
        current2 = current2->next;
    }
    return resultHead;
}

int main(void) {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    struct Node* result = NULL;

    append(&list1, 10);
    append(&list1, 20);
    append(&list1, 30);

    append(&list2, 2);
    append(&list2, 4);
    append(&list2, 5);

    result = divideLists(list1, list2);

    if (result != NULL) {
        printList(result);
        freeList(result);
    } else {
        printf("Error: Division by zero or lists of unequal lengths not handled beyond shortest length.\n");
    }

    freeList(list1);
    freeList(list2);

    return EXIT_SUCCESS;
}