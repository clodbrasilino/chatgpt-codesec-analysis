#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct SublistNode {
    Node* sublist;
    struct SublistNode* next;
} SublistNode;

int* get_first_elements(SublistNode* head, int* count) {
    if (head == NULL || count == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        return NULL;
    }

    int num_sublists = 0;
    SublistNode* current = head;
    while (current != NULL) {
        num_sublists++;
        current = current->next;
    }

    int* first_elements = (int*)malloc(num_sublists * sizeof(int));
    if (first_elements == NULL) {
        *count = 0;
        return NULL;
    }

    current = head;
    int index = 0;
    while (current != NULL) {
        if (current->sublist != NULL) {
            first_elements[index] = current->sublist->data;
        } else {
            first_elements[index] = 0; 
        }
        index++;
        current = current->next;
    }

    *count = num_sublists;
    return first_elements;
}

void free_sublists(SublistNode* head) {
    SublistNode* current_sublist = head;
    while (current_sublist != NULL) {
        Node* current_node = current_sublist->sublist;
        while (current_node != NULL) {
            Node* temp_node = current_node;
            current_node = current_node->next;
            free(temp_node);
        }
        SublistNode* temp_sublist = current_sublist;
        current_sublist = current_sublist->next;
        free(temp_sublist);
    }
}

int main() {
    SublistNode* head = (SublistNode*)malloc(sizeof(SublistNode));
    if (head == NULL) return 1;

    head->sublist = (Node*)malloc(sizeof(Node));
    if (head->sublist == NULL) {
        free(head);
        return 1;
    }
    head->sublist->data = 10;
    head->sublist->next = NULL;

    head->next = (SublistNode*)malloc(sizeof(SublistNode));
    if (head->next == NULL) {
        free_sublists(head);
        return 1;
    }

    head->next->sublist = (Node*)malloc(sizeof(Node));
    if (head->next->sublist == NULL) {
        free_sublists(head);
        return 1;
    }
    head->next->sublist->data = 20;
    head->next->sublist->next = NULL;
    head->next->next = NULL;

    int count = 0;
    int* first_elements = get_first_elements(head, &count);

    if (first_elements != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%d\n", first_elements[i]);
        }
        free(first_elements);
    }

    free_sublists(head);

    return 0;
}