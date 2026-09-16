#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *shift_last_to_first(struct Node *head)
{
    struct Node *last;
    struct Node *second_last;

    if (head == NULL || head->next == NULL) {
        return head;
    }

    second_last = head;
    last = head->next;

    while (last->next != NULL) {
        second_last = last;
        last = last->next;
    }

    second_last->next = NULL;
    last->next = head;
    head = last;

    return head;
}

struct Node *create_node(int data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

void append_node(struct Node **head, int data)
{
    struct Node *new_node = create_node(data);
    struct Node *temp;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    temp = *head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_node;
}

void print_list(const struct Node *head)
{
    const struct Node *temp = head;

    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf("\n");
}

void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void)
{
    struct Node *head = NULL;
    int values[] = {1, 2, 3, 4, 5};
    size_t i;
    size_t count = sizeof(values) / sizeof(values[0]);

    for (i = 0; i < count; i++) {
        append_node(&head, values[i]);
    }

    printf("Original list: ");
    print_list(head);

    head = shift_last_to_first(head);

    printf("List after shifting last element to first: ");
    print_list(head);

    free_list(head);

    return 0;
}