#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int append_node(Node **head, int data) {
    if (head == NULL) {
        return -1;
    }
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = new_node;
        return 0;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return 0;
}

int split_list(Node *head, size_t k, Node **first_part, Node **second_part) {
    if (first_part == NULL || second_part == NULL) {
        return -1;
    }

    if (head == NULL) {
        if (k > 0) {
            return -2;
        }
        *first_part = NULL;
        *second_part = NULL;
        return 0;
    }

    if (k == 0) {
        *first_part = NULL;
        *second_part = head;
        return 0;
    }

    Node *current = head;
    size_t count = 1;

    while (current->next != NULL && count < k) {
        current = current->next;
        count++;
    }

    if (count < k) {
        return -2;
    }

    *first_part = head;
    *second_part = current->next;
    current->next = NULL;

    return 0;
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
    Node *list = NULL;

    if (append_node(&list, 1) != 0 ||
        append_node(&list, 2) != 0 ||
        append_node(&list, 3) != 0 ||
        append_node(&list, 4) != 0 ||
        append_node(&list, 5) != 0) {
        fprintf(stderr, "Allocation failed\n");
        free_list(list);
        return 1;
    }

    Node *part1 = NULL;
    Node *part2 = NULL;
    size_t k = 2;

    if (split_list(list, k, &part1, &part2) != 0) {
        fprintf(stderr, "Split failed\n");
        free_list(list);
        return 1;
    }

    print_list(part1);
    print_list(part2);

    free_list(part1);
    free_list(part2);

    return 0;
}