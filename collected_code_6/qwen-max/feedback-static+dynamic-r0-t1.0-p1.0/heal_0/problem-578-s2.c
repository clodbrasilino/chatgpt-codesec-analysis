#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

Node* interleave_lists(Node *list1, Node *list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }
    
    Node *result_head = NULL;
    Node **current_ptr = &result_head;

    while (list1 != NULL && list2 != NULL) {
        *current_ptr = list1;
        list1 = list1->next;
        (*current_ptr)->next = list2;
        current_ptr = &((*current_ptr)->next);
        list2 = list2->next;
    }

    if (list1 != NULL) {
        *current_ptr = list1;
    } else if (list2 != NULL) {
        *current_ptr = list2;
    }

    return result_head;
}

int main() {
    Node *list1 = create_node(1);
    list1->next = create_node(3);
    list1->next->next = create_node(5);

    Node *list2 = create_node(2);
    list2->next = create_node(4);
    list2->next->next = create_node(6);

    Node *result = interleave_lists(list1, list2);

    for (Node *current = result; current != NULL; current = current->next) {
        printf("%d ", current->value);
    }

    free_list(result);

    return 0;
}