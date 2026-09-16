#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *append_node(Node **head, int data) {
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    return new_node;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

Node *create_alternate_list(const Node *head) {
    Node *new_head = NULL;
    Node *tail = NULL;
    int take = 1;

    while (head != NULL) {
        if (take) {
            Node *new_node = malloc(sizeof(*new_node));
            if (new_node == NULL) {
                free_list(new_head);
                return NULL;
            }
            new_node->data = head->data;
            new_node->next = NULL;

            if (new_head == NULL) {
                new_head = new_node;
            } else {
                tail->next = new_node;
            }
            tail = new_node;
        }

        take = !take;
        head = head->next;
    }

    return new_head;
}

int main(void) {
    Node *list = NULL;
    int values[] = {1, 2, 3, 4, 5, 6, 7};
    size_t i;

    for (i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        if (append_node(&list, values[i]) == NULL) {
            free_list(list);
            return 1;
        }
    }

    Node *alternate = create_alternate_list(list);

    if (alternate == NULL && list != NULL) {
        free_list(list);
        return 1;
    }

    Node *current = alternate;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    free_list(alternate);
    free_list(list);

    return 0;
}