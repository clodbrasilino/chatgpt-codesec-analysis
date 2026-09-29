#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append(Node **head, int data) {
    Node *new_node = create_node(data);
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

int list_length(Node *head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

Node* find_max_length_list(Node *list1, Node *list2) {
    if (list_length(list1) >= list_length(list2)) {
        return list1;
    } else {
        return list2;
    }
}

int main() {
    Node *list1 = NULL;
    Node *list2 = NULL;

    append(&list1, 1);
    append(&list1, 2);
    append(&list1, 3);

    append(&list2, 4);
    append(&list2, 5);

    Node *max_list = find_max_length_list(list1, list2);

    Node *current = max_list;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    return 0;
}