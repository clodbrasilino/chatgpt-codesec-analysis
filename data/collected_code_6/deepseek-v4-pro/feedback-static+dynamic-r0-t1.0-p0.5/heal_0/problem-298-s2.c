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

bool contains_element(Node* list, int value) {
    Node* current = list;
    while (current != NULL) {
        if (current->data == value) {
            return true;
        }
        if (current->child != NULL && contains_element(current->child, value)) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Node* find_common_elements(Node* list1, Node* list2) {
    Node* result = NULL;
    Node* result_tail = NULL;
    Node* current = list1;
    
    while (current != NULL) {
        if (contains_element(list2, current->data)) {
            Node* new_node = create_node(current->data);
            if (result == NULL) {
                result = new_node;
                result_tail = new_node;
            } else {
                result_tail->next = new_node;
                result_tail = new_node;
            }
        }
        if (current->child != NULL) {
            Node* child_result = find_common_elements(current->child, list2);
            if (child_result != NULL) {
                if (result == NULL) {
                    result = child_result;
                    result_tail = child_result;
                    while (result_tail->next != NULL) {
                        result_tail = result_tail->next;
                    }
                } else {
                    result_tail->next = child_result;
                    while (result_tail->next != NULL) {
                        result_tail = result_tail->next;
                    }
                }
            }
        }
        current = current->next;
    }
    
    return result;
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
        if (current->child != NULL) {
            printf("(");
            print_list(current->child);
            printf(")");
        }
        current = current->next;
    }
}

int main() {
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
    
    Node* common = find_common_elements(list1, list2);
    
    printf("Common elements: ");
    print_list(common);
    printf("\n");
    
    free_list(list1);
    free_list(list2);
    free_list(common);
    
    return 0;
}