#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListNode {
    Node* list;
    struct ListNode* next;
} ListNode;

ListNode* createListNode(Node* list) {
    ListNode* newListNode = (ListNode*)malloc(sizeof(ListNode));
    if (newListNode == NULL) {
        return NULL;
    }
    newListNode->list = list;
    newListNode->next = NULL;
    return newListNode;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void freeListOfLists(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        ListNode* temp = current;
        freeList(current->list);
        current = current->next;
        free(temp);
    }
}

ListNode* removeEmptyLists(ListNode* head) {
    if (head == NULL) {
        return NULL;
    }
    
    ListNode* current = head;
    ListNode* prev = NULL;
    
    while (current != NULL) {
        if (current->list == NULL) {
            ListNode* toDelete = current;
            if (prev == NULL) {
                head = current->next;
                current = head;
            } else {
                prev->next = current->next;
                current = current->next;
            }
            free(toDelete);
        } else {
            prev = current;
            current = current->next;
        }
    }
    
    return head;
}

void printListOfLists(ListNode* head) {
    ListNode* current = head;
    int listIndex = 0;
    
    while (current != NULL) {
        printf("List %d: ", listIndex);
        Node* node = current->list;
        if (node == NULL) {
            printf("(empty)");
        }
        while (node != NULL) {
            printf("%d ", node->data);
            node = node->next;
        }
        printf("\n");
        current = current->next;
        listIndex++;
    }
}

int main() {
    ListNode* head = NULL;
    ListNode* tail = NULL;
    
    Node* list1 = createNode(1);
    list1->next = createNode(2);
    list1->next->next = createNode(3);
    
    Node* list2 = NULL;
    
    Node* list3 = createNode(4);
    
    Node* list4 = NULL;
    
    ListNode* ln1 = createListNode(list1);
    ListNode* ln2 = createListNode(list2);
    ListNode* ln3 = createListNode(list3);
    ListNode* ln4 = createListNode(list4);
    
    head = ln1;
    ln1->next = ln2;
    ln2->next = ln3;
    ln3->next = ln4;
    /* Possible weaknesses found:
     *  Value stored to 'tail' is never read [deadcode.DeadStores]
     *  Variable 'tail' is assigned a value that is never used. [unreadVariable]
     */
    tail = ln4;
    
    printf("Original list of lists:\n");
    printListOfLists(head);
    
    head = removeEmptyLists(head);
    
    printf("\nAfter removing empty lists:\n");
    printListOfLists(head);
    
    freeListOfLists(head);
    
    return 0;
}