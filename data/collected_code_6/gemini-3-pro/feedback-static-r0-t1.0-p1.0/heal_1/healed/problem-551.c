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

void appendList(struct List** head_ref, struct Node* new_node) {
    if (head_ref == NULL) {
        return;
    }
    
    struct List* new_list = (struct List*)malloc(sizeof(struct List));
    if (new_list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_list->head = new_node;
    new_list->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_list;
    } else {
        struct List* last = *head_ref;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_list;
    }
}

void appendNode(struct Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
    } else {
        struct Node* last = *head_ref;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
    }
}

struct Node* extractColumn(struct List* nested_list, int column_index) {
    if (nested_list == NULL || column_index < 0) {
        return NULL;
    }

    struct Node* result = NULL;
    struct List* current_list = nested_list;

    while (current_list != NULL) {
        struct Node* current_node = current_list->head;
        int i = 0;
        
        while (current_node != NULL && i < column_index) {
            current_node = current_node->next;
            i++;
        }
        
        if (current_node != NULL && i == column_index) {
            appendNode(&result, current_node->data);
        }
        
        current_list = current_list->next;
    }

    return result;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void freeNodeList(struct Node* head) {
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void freeNestedList(struct List* head) {
    while (head != NULL) {
        struct List* temp = head;
        head = head->next;
        freeNodeList(temp->head);
        free(temp);
    }
}

int main(void) {
    struct List* nested_list = NULL;

    struct Node* row1 = NULL;
    appendNode(&row1, 1);
    appendNode(&row1, 2);
    appendNode(&row1, 3);
    appendList(&nested_list, row1);

    struct Node* row2 = NULL;
    appendNode(&row2, 4);
    appendNode(&row2, 5);
    appendList(&nested_list, row2);

    struct Node* row3 = NULL;
    appendNode(&row3, 7);
    appendNode(&row3, 8);
    appendNode(&row3, 9);
    appendNode(&row3, 10);
    appendList(&nested_list, row3);

    struct Node* column = extractColumn(nested_list, 1);
    
    if (column != NULL) {
        printList(column);
        freeNodeList(column);
    }

    freeNestedList(nested_list);

    return 0;
}