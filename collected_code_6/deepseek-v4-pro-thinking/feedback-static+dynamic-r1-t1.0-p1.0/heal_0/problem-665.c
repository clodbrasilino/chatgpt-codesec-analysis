#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void shift_first_element_to_end(struct Node **head) {
    if (head == NULL || *head == NULL || (*head)->next == NULL) {
        return;
    }

    struct Node *first = *head;
    *head = first->next;
    first->next = NULL;

    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = first;
}

int main(void) {
    struct Node *head = NULL;
    struct Node *tail = NULL;
    int values[] = {1, 2, 3, 4};
    size_t count = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < count; ++i) {
        struct Node *new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            while (head != NULL) {
                struct Node *temp = head;
                head = head->next;
                free(temp);
            }
            return 1;
        }

        new_node->data = values[i];
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    shift_first_element_to_end(&head);

    for (struct Node *current = head; current != NULL; current = current->next) {
        printf("%d ", current->data);
    }
    printf("\n");

    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}