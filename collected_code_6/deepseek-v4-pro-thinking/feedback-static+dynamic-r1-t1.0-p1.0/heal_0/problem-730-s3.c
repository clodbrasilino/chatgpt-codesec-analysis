#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data)
{
    struct Node *node = malloc(sizeof(*node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

int append_node(struct Node **head, int data)
{
    struct Node *node = create_node(data);
    if (node == NULL) {
        return 0;
    }
    if (*head == NULL) {
        *head = node;
        return 1;
    }
    struct Node *tail = *head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
    return 1;
}

void remove_consecutive_duplicates(struct Node **head)
{
    if (head == NULL || *head == NULL) {
        return;
    }
    struct Node *current = *head;
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            struct Node *duplicate = current->next;
            current->next = duplicate->next;
            free(duplicate);
        } else {
            current = current->next;
        }
    }
}

void print_list(const struct Node *head)
{
    for (const struct Node *current = head; current != NULL; current = current->next) {
        printf("%d ", current->data);
    }
    printf("\n");
}

void free_list(struct Node **head)
{
    if (head == NULL) {
        return;
    }
    while (*head != NULL) {
        struct Node *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main(void)
{
    struct Node *head = NULL;
    int values[] = {1, 1, 2, 3, 3, 3, 4, 1};
    int count = sizeof(values) / sizeof(values[0]);
    int i;

    for (i = 0; i < count; ++i) {
        if (!append_node(&head, values[i])) {
            free_list(&head);
            return EXIT_FAILURE;
        }
    }

    print_list(head);
    remove_consecutive_duplicates(&head);
    print_list(head);
    free_list(&head);

    return EXIT_SUCCESS;
}