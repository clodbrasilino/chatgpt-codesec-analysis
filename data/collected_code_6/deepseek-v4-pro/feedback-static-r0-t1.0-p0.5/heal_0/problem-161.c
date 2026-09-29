#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

int contains(Node *head, int value) {
    Node *current = head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void remove_elements(Node **list1, Node *list2) {
    if (list1 == NULL || *list1 == NULL || list2 == NULL) {
        return;
    }

    Node *current = *list1;
    Node *prev = NULL;

    while (current != NULL) {
        if (contains(list2, current->data)) {
            Node *temp = current;
            if (prev == NULL) {
                *list1 = current->next;
                current = *list1;
            } else {
                prev->next = current->next;
                current = current->next;
            }
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
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

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;

    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 3);
    append_node(&list1, 4);
    append_node(&list1, 5);

    append_node(&list2, 2);
    append_node(&list2, 4);
    append_node(&list2, 6);

    printf("List 1 before removal: ");
    print_list(list1);
    printf("List 2: ");
    print_list(list2);

    remove_elements(&list1, list2);

    printf("List 1 after removal: ");
    print_list(list1);

    free_list(list1);
    free_list(list2);

    return 0;
}