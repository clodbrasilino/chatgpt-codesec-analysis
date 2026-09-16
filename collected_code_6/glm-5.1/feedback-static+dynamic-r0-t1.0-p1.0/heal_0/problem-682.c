#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void append_node(struct Node **head, int data) {
    struct Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
    } else {
        struct Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

struct Node *multiply_lists(struct Node *list1, struct Node *list2) {
    struct Node *result = NULL;
    struct Node **tail = &result;

    while (list1 != NULL && list2 != NULL) {
        int product = list1->data * list2->data;
        struct Node *new_node = create_node(product);
        *tail = new_node;
        tail = &((*tail)->next);
        list1 = list1->next;
        list2 = list2->next;
    }

    return result;
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

void print_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;

    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 3);

    append_node(&list2, 4);
    append_node(&list2, 5);
    append_node(&list2, 6);

    struct Node *result = multiply_lists(list1, list2);

    print_list(result);

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}