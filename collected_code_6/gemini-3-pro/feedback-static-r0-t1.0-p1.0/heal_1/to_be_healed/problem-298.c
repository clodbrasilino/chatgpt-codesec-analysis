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
    NestedList* new_node = (NestedList*)malloc(sizeof(NestedList));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->inner_list = inner_list;
    new_node->next = NULL;
    return new_node;
}

bool contains(Node* list, int value) {
    Node* current = list;
    while (current != NULL) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void append_unique(Node** head, int value) {
    if (!contains(*head, value)) {
        Node* new_node = create_node(value);
        if (*head == NULL) {
            *head = new_node;
        } else {
            Node* current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
    }
}

Node* find_common_elements(NestedList* nested, Node* target_list) {
    Node* result = NULL;
    NestedList* current_nested = nested;

    while (current_nested != NULL) {
        Node* inner = current_nested->inner_list;
        while (inner != NULL) {
            if (contains(target_list, inner->data)) {
                append_unique(&result, inner->data);
            }
            inner = inner->next;
        }
        current_nested = current_nested->next;
    }
    return result;
}

void free_list(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void free_nested_list(NestedList* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    NestedList* tmp;
    while (head != NULL) {
        tmp = head;
        free_list(head->inner_list);
        head = head->next;
        free(tmp);
    }
}

void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* target = create_node(2);
    target->next = create_node(4);
    target->next->next = create_node(6);
    target->next->next->next = create_node(8);

    Node* list1 = create_node(1);
    list1->next = create_node(2);
    list1->next->next = create_node(3);

    Node* list2 = create_node(4);
    list2->next = create_node(5);
    list2->next->next = create_node(6);

    NestedList* nested = create_nested_node(list1);
    nested->next = create_nested_node(list2);

    Node* common = find_common_elements(nested, target);

    print_list(common);

    free_list(target);
    free_nested_list(nested);
    free_list(common);

    return EXIT_SUCCESS;
}