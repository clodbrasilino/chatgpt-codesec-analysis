#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct NestedList {
    Node* inner_list;
    struct NestedList* next;
} NestedList;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

NestedList* create_nested_node(Node* inner_list) {
    NestedList* new_nested = (NestedList*)malloc(sizeof(NestedList));
    if (!new_nested) {
        exit(EXIT_FAILURE);
    }
    new_nested->inner_list = inner_list;
    new_nested->next = NULL;
    return new_nested;
}

void append_node(Node** head, int data) {
    Node* new_node = create_node(data);
    if (!*head) {
        *head = new_node;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new_node;
}

void append_nested(NestedList** head, Node* inner_list) {
    NestedList* new_nested = create_nested_node(inner_list);
    if (!*head) {
        *head = new_nested;
        return;
    }
    NestedList* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new_nested;
}

bool contains(Node* list, int value) {
    Node* temp = list;
    while (temp) {
        if (temp->data == value) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

Node* find_common_elements(NestedList* nested_list, Node* target_list) {
    Node* result = NULL;
    NestedList* curr_nested = nested_list;
    
    while (curr_nested) {
        Node* curr_inner = curr_nested->inner_list;
        while (curr_inner) {
            if (contains(target_list, curr_inner->data) && !contains(result, curr_inner->data)) {
                append_node(&result, curr_inner->data);
            }
            curr_inner = curr_inner->next;
        }
        curr_nested = curr_nested->next;
    }
    
    return result;
}

void free_list(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_nested_list(NestedList* head) {
    while (head) {
        NestedList* temp = head;
        head = head->next;
        free_list(temp->inner_list);
        free(temp);
    }
}

void print_list(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {
    Node* l1 = NULL;
    append_node(&l1, 1);
    append_node(&l1, 2);
    append_node(&l1, 3);
    
    Node* l2 = NULL;
    append_node(&l2, 3);
    append_node(&l2, 4);
    append_node(&l2, 5);
    
    NestedList* nested = NULL;
    append_nested(&nested, l1);
    append_nested(&nested, l2);
    
    Node* target = NULL;
    append_node(&target, 2);
    append_node(&target, 3);
    append_node(&target, 5);
    append_node(&target, 9);
    
    Node* result = find_common_elements(nested, target);
    
    print_list(result);
    
    free_list(result);
    free_list(target);
    free_nested_list(nested);
    
    return 0;
}