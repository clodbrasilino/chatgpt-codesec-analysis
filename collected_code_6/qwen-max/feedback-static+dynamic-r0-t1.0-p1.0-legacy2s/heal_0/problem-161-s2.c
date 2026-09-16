#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) return NULL;
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

struct Node* removeElements(struct Node* mainList, struct Node* toRemove) {
    struct Node dummy;
    dummy.next = mainList;
    struct Node* current = &dummy;

    while (current->next != NULL) {
        struct Node* runner = toRemove;
        int found = 0;
        while (runner != NULL && !found) {
            if (current->next->data == runner->data) {
                found = 1;
            } else {
                runner = runner->next;
            }
        }
        if (found) {
            struct Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }

    return dummy.next;
}

void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* mainList = NULL;
    struct Node* toRemove = NULL;

    append(&mainList, 1);
    append(&mainList, 2);
    append(&mainList, 3);
    append(&mainList, 4);

    append(&toRemove, 2);
    append(&toRemove, 3);

    mainList = removeElements(mainList, toRemove);

    struct Node* current = mainList;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    freeList(mainList);
    freeList(toRemove);

    return 0;
}