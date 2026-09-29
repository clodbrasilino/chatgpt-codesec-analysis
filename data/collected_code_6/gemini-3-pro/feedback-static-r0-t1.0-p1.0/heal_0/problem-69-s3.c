#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

bool isSublist(Node* list, Node* sublist) {
    if (sublist == NULL) {
        return true;
    }
    if (list == NULL) {
        return false;
    }

    Node* currentList = list;
    
    while (currentList != NULL) {
        Node* ptr1 = currentList;
        Node* ptr2 = sublist;
        
        while (ptr1 != NULL && ptr2 != NULL && ptr1->data == ptr2->data) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        
        if (ptr2 == NULL) {
            return true;
        }
        
        currentList = currentList->next;
    }
    
    return false;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

void append(Node** head, int data) {
    if (head == NULL) return;
    
    Node* newNode = createNode(data);
    if (newNode == NULL) return;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node* list = NULL;
    Node* sublist = NULL;

    append(&list, 1);
    append(&list, 2);
    append(&list, 3);
    append(&list, 4);
    append(&list, 5);

    append(&sublist, 3);
    append(&sublist, 4);

    if (isSublist(list, sublist)) {
        printf("The sublist is present in the list.\n");
    } else {
        printf("The sublist is not present in the list.\n");
    }

    freeList(list);
    freeList(sublist);

    return 0;
}