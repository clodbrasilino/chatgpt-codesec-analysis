#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int value) {
    Node *new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

Node* divide_lists(Node *list1, Node *list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }

    Node *result = NULL;
    Node *current1 = list1;
    Node *current2 = list2;

    while (current1 != NULL && current2 != NULL) {
        if (current1->value % current2->value == 0) {
            append_node(&result, current1->value / current2->value);
        }
        current1 = current1->next;
        current2 = current2->next;
    }

    return result;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Node *list1 = NULL;
    Node *list2 = NULL;

    append_node(&list1, 10);
    append_node(&list1, 20);
    append_node(&list1, 30);

    append_node(&list2, 2);
    append_node(&list2, 5);
    append_node(&list2, 3);

    Node *result = divide_lists(list1, list2);

    print_list(result);

    return 0;
}