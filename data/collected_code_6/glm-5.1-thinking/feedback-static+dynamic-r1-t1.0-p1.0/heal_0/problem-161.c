#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int list_contains(Node *head, int value) {
    Node *current = head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Node *remove_elements(Node *list1, Node *list2) {
    if (list1 == NULL || list2 == NULL) {
        return list1;
    }
    Node **indirect = &list1;
    while (*indirect != NULL) {
        if (list_contains(list2, (*indirect)->data)) {
            Node *to_delete = *indirect;
            *indirect = (*indirect)->next;
            free(to_delete);
        } else {
            indirect = &(*indirect)->next;
        }
    }
    return list1;
}

Node *create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
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

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

Node *append_node(Node *head, int value) {
    Node *new_node = create_node(value);
    if (new_node == NULL) {
        free_list(head);
        exit(EXIT_FAILURE);
    }
    if (head == NULL) {
        return new_node;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

int main(void) {
    Node *list1 = NULL;
    list1 = append_node(list1, 1);
    list1 = append_node(list1, 2);
    list1 = append_node(list1, 3);
    list1 = append_node(list1, 4);
    list1 = append_node(list1, 5);

    Node *list2 = NULL;
    list2 = append_node(list2, 2);
    list2 = append_node(list2, 4);

    list1 = remove_elements(list1, list2);

    print_list(list1);

    free_list(list1);
    free_list(list2);

    return 0;
}