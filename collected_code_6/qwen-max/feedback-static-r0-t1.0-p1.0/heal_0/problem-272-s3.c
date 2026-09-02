#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct ListNode {
    Tuple data;
    struct ListNode *next;
} ListNode;

Tuple* extractRearElement(ListNode **head) {
    if (*head == NULL) return NULL;

    ListNode *current = *head;
    ListNode *previous = NULL;

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        *head = NULL;
    } else {
        previous->next = NULL;
    }
    
    Tuple *rearElement = (Tuple *)malloc(sizeof(Tuple));
    if (rearElement == NULL) return NULL;
    rearElement->key = current->data.key;
    rearElement->value = current->data.value;
    free(current);
    return rearElement;
}

int main() {
    ListNode *head = (ListNode *)malloc(sizeof(ListNode));
    head->data.key = 1;
    head->data.value = 20;
    head->next = (ListNode *)malloc(sizeof(ListNode));
    head->next->data.key = 2;
    head->next->data.value = 30;
    head->next->next = NULL;

    Tuple *rearElement = extractRearElement(&head);
    if (rearElement != NULL) {
        printf("Rear Element: Key = %d, Value = %d\n", rearElement->key, rearElement->value);
        free(rearElement);
    } else {
        printf("List is empty or memory allocation failed.\n");
    }

    while (head != NULL) {
        ListNode *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}