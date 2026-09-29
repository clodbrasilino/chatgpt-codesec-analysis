#include <stdio.h>
#include <stdlib.h>

struct node {
    int sublist[2];
    struct node *next;
};

typedef struct node ListNode;

ListNode* newNode(int a, int b) {
    ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
    if (temp == NULL) {
        exit(0);
    }
    temp->sublist[0] = a;
    temp->sublist[1] = b;
    temp->next = NULL;
    return temp;
}

void sortedInsert(ListNode** head_ref, ListNode* new_node) {
    ListNode* current;

    if (*head_ref == NULL || (*head_ref)->sublist[1] >= new_node->sublist[1]) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    } else {
        current = *head_ref;
        while (current->next != NULL && current->next->sublist[1] < new_node->sublist[1]) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void insertionSort(ListNode **head_ref) {
    ListNode *sorted = NULL;
    ListNode *current = *head_ref;

    while (current != NULL) {
        ListNode *next = current->next;
        sortedInsert(&sorted, current);
        current = next;
    }

    *head_ref = sorted;
}

void printList(ListNode *head) {
    ListNode *temp = head;
    while(temp != NULL) {
        printf(" [%d , %d] ", temp->sublist[0],temp->sublist[1]);
        temp = temp->next;
    }
}

int main() {
    ListNode *a = NULL;
    a = newNode(5, 2);
    a->next = newNode(2, 3);
    a->next->next = newNode(4, 1);
    a->next->next->next = newNode(3, 5);
    
    printf("Linked List before sorting \n");
    printList(a);
    
    insertionSort(&a);
    
    printf("\nLinked List after sorting \n");
    printList(a);

    return 0;
}