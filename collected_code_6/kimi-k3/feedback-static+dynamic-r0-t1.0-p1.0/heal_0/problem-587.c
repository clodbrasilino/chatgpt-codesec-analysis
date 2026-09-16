#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple* list_to_tuple(ListNode *head) {
    if (head == NULL) {
        return NULL;
    }
    
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    size_t count = 0;
    ListNode *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    tuple->elements = (int*)malloc(count * sizeof(int));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }
    
    tuple->size = count;
    current = head;
    size_t index = 0;
    while (current != NULL) {
        tuple->elements[index] = current->data;
        index++;
        current = current->next;
    }
    
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        if (tuple->elements != NULL) {
            free(tuple->elements);
        }
        free(tuple);
    }
}

ListNode* create_node(int data) {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void free_list(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    ListNode *head = create_node(1);
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    
    head->next = create_node(2);
    if (head->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    
    head->next->next = create_node(3);
    if (head->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    
    head->next->next->next = create_node(4);
    if (head->next->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    
    head->next->next->next->next = create_node(5);
    if (head->next->next->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    
    Tuple *tuple = list_to_tuple(head);
    if (tuple == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }
    
    printf("Tuple: (");
    for (size_t i = 0; i < tuple->size; i++) {
        printf("%d", tuple->elements[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
    
    free_tuple(tuple);
    free_list(head);
    
    return EXIT_SUCCESS;
}