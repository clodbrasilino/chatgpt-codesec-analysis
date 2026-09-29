#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct List {
    struct Node* head;
    struct List* next;
};

void freeList(struct List* head) {
    while (head != NULL) {
        struct List* temp_list = head;
        head = head->next;
        struct Node* curr_node = temp_list->head;
        while (curr_node != NULL) {
            struct Node* temp_node = curr_node;
            curr_node = curr_node->next;
            free(temp_node);
        }
        free(temp_list);
    }
}

int removeColumn(struct List* head, int col) {
    if (head == NULL || col < 0) {
        return -1;
    }

    struct List* curr_list = head;
    while (curr_list != NULL) {
        if (curr_list->head == NULL) {
            curr_list = curr_list->next;
            continue;
        }

        if (col == 0) {
            struct Node* temp = curr_list->head;
            curr_list->head = curr_list->head->next;
            free(temp);
        } else {
            struct Node* curr_node = curr_list->head;
            int i = 0;
            while (curr_node != NULL && i < col - 1) {
                curr_node = curr_node->next;
                i++;
            }
            if (curr_node != NULL && curr_node->next != NULL) {
                struct Node* temp = curr_node->next;
                curr_node->next = curr_node->next->next;
                free(temp);
            }
        }
        curr_list = curr_list->next;
    }
    return 0;
}

void printList(struct List* head) {
    while (head != NULL) {
        struct Node* curr = head->head;
        while (curr != NULL) {
            printf("%d ", curr->data);
            curr = curr->next;
        }
        printf("\n");
        head = head->next;
    }
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct List* createRow(int a, int b, int c) {
    struct List* newRow = (struct List*)malloc(sizeof(struct List));
    if (!newRow) return NULL;
    
    struct Node* n1 = createNode(a);
    struct Node* n2 = createNode(b);
    struct Node* n3 = createNode(c);
    
    if (!n1 || !n2 || !n3) {
        free(n1); free(n2); free(n3); free(newRow);
        return NULL;
    }
    
    n1->next = n2;
    n2->next = n3;
    newRow->head = n1;
    newRow->next = NULL;
    
    return newRow;
}

int main(void) {
    struct List* row1 = createRow(1, 2, 3);
    struct List* row2 = createRow(4, 5, 6);
    struct List* row3 = createRow(7, 8, 9);
    
    if (!row1 || !row2 || !row3) {
        freeList(row1); freeList(row2); freeList(row3);
        return 1;
    }
    
    row1->next = row2;
    row2->next = row3;
    
    int result = removeColumn(row1, 1);
    if (result == 0) {
        printList(row1);
    }
    
    freeList(row1);
    
    return 0;
}