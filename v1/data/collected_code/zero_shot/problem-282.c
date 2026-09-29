#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

void subtractLists(struct Node* list1, struct Node* list2) {
    struct Node* result = NULL;
    struct Node* temp = NULL;
    struct Node* temp2 = NULL;

    while (list1 != NULL) {
        int exist = 0;
        temp = list2;
        while (temp != NULL) {
            if (list1->data == temp->data) {
                exist = 1;
                break;
            }
            temp = temp->next;
        }
        if (exist == 0) {
            // Add the current node to the result list
            struct Node* node = (struct Node*)malloc(sizeof(struct Node));
            node->data = list1->data;
            node->next = NULL;
            if (result == NULL) {
                result = node;
            } else {
                temp2 = result;
                while (temp2->next != NULL) {
                    temp2 = temp2->next;
                }
                temp2->next = node;
            }
        }
        list1 = list1->next;
    }

    // Print the result list
    temp = result;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    
    // Initialize list1
    list1 = (struct Node*)malloc(sizeof(struct Node));
    list1->data = 1;
    list1->next = (struct Node*)malloc(sizeof(struct Node));
    list1->next->data = 2;
    list1->next->next = (struct Node*)malloc(sizeof(struct Node));
    list1->next->next->data = 3;
    list1->next->next->next = NULL;

    // Initialize list2
    list2 = (struct Node*)malloc(sizeof(struct Node));
    list2->data = 2;
    list2->next = (struct Node*)malloc(sizeof(struct Node));
    list2->next->data = 3;
    list2->next->next = (struct Node*)malloc(sizeof(struct Node));
    list2->next->next->data = 4;
    list2->next->next->next = NULL;

    subtractLists(list1, list2);

    return 0;
}