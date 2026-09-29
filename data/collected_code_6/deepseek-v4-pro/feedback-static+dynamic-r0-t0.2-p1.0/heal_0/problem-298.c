#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* child;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->child = NULL;
    return new_node;
}

bool contains(Node* list, int value) {
    Node* current = list;
    while (current != NULL) {
        if (current->data == value) {
            return true;
        }
        if (current->child != NULL && contains(current->child, value)) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void find_common_elements(Node* list1, Node* list2, Node** result) {
    if (list1 == NULL || list2 == NULL) {
        return;
    }
    
    Node* current = list1;
    while (current != NULL) {
        if (contains(list2, current->data)) {
            Node* new_node = create_node(current->data);
            new_node->next = *result;
            *result = new_node;
        }
        if (current->child != NULL) {
            find_common_elements(current->child, list2, result);
        }
        current = current->next;
    }
}

void free_list(Node* list) {
    Node* current = list;
    while (current != NULL) {
        Node* next = current->next;
        if (current->child != NULL) {
            free_list(current->child);
        }
        free(current);
        current = next;
    }
}

void print_list(Node* list) {
    Node* current = list;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* list1 = create_node(1);
    list1->next = create_node(2);
    list1->next->next = create_node(3);
    list1->next->child = create_node(4);
    list1->next->child->next = create_node(5);
    list1->next->next->child = create_node(6);
    
    Node* list2 = create_node(2);
    list2->next = create_node(4);
    list2->next->next = create_node(6);
    list2->next->next->next = create_node(8);
    
    Node* result = NULL;
    find_common_elements(list1, list2, &result);
    
    printf("Common elements: ");
    print_list(result);
    
    free_list(list1);
    free_list(list2);
    free_list(result);
    
    return 0;
}