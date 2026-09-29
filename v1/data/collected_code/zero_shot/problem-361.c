#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

void removeEmptyLists(Node** head) {
    Node* curr = *head;
    Node* prev = NULL;

    while (curr != NULL) {
        if (curr->data == -1) {
            if (prev == NULL) {
                *head = curr->next;
                free(curr);
                curr = *head;
            } else {
                prev->next = curr->next;
                free(curr);
                curr = prev->next;
            }
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

int main() {
    Node* list1 = (Node*)malloc(sizeof(Node));
    Node* list2 = (Node*)malloc(sizeof(Node));

    list1->data = -1;
    list1->next = list2;
    list2->data = 2;
    list2->next = NULL;

    removeEmptyLists(&list1);

    Node* temp = list1;
    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->next;
    }

    return 0;
}