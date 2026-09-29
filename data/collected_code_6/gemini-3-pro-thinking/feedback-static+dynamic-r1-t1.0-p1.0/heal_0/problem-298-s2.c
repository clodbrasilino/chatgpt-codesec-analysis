#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct NestedList {
    Node* sublist;
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

NestedList* create_nested_node(Node* sublist) {
    NestedList* new_node = (NestedList*)malloc(sizeof(NestedList));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->sublist = sublist;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node** head, int data) {
    if (!head) {
        return;
    }
    Node* new_node = create_node(data);
    if (!*head) {
        *head = new_node;
        return;
    }
    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
}

void append_nested_node(NestedList** head, Node* sublist) {
    if (!head) {
        return;
    }
    NestedList* new_node = create_nested_node(sublist);
    if (!*head) {
        *head = new_node;
        return;
    }
    NestedList* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
}

bool contains(Node* list, int value) {
    Node* current = list;
    while (current) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Node* find_common_elements(NestedList* nested, Node* target) {
    Node* result = NULL;
    NestedList* current_nested = nested;
    
    while (current_nested) {
        Node* current_sublist = current_nested->sublist;
        while (current_sublist) {
            if (contains(target, current_sublist->data)) {
                if (!contains(result, current_sublist->data)) {
                    append_node(&result, current_sublist->data);
                }
            }
            current_sublist = current_sublist->next;
        }
        current_nested = current_nested->next;
    }
    
    return result;
}

void free_list(Node* head) {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void free_nested_list(NestedList* head) {
    NestedList* current = head;
    while (current) {
        NestedList* temp = current;
        current = current->next;
        free(temp);
    }
}

void print_list(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* target_list = NULL;
    append_node(&target_list, 2);
    append_node(&target_list, 5);
    append_node(&target_list, 8);
    append_node(&target_list, 10);

    Node* sublist1 = NULL;
    append_node(&sublist1, 1);
    append_node(&sublist1, 2);
    append_node(&sublist1, 3);

    Node* sublist2 = NULL;
    append_node(&sublist2, 5);
    append_node(&sublist2, 6);
    append_node(&sublist2, 7);

    Node* sublist3 = NULL;
    append_node(&sublist3, 8);
    append_node(&sublist3, 9);
    append_node(&sublist3, 10);

    NestedList* nested_list = NULL;
    append_nested_node(&nested_list, sublist1);
    append_nested_node(&nested_list, sublist2);
    append_nested_node(&nested_list, sublist3);

    Node* common_elements = find_common_elements(nested_list, target_list);

    print_list(common_elements);

    free_list(target_list);
    free_list(sublist1);
    free_list(sublist2);
    free_list(sublist3);
    free_nested_list(nested_list);
    free_list(common_elements);

    return 0;
}