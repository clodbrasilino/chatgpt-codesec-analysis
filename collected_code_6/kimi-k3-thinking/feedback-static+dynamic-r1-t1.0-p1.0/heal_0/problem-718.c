#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data);
struct Node *alternate_elements(const struct Node *head);
void print_list(const struct Node *head);
void free_list(struct Node *head);

struct Node *create_node(int data)
{
    struct Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

struct Node *alternate_elements(const struct Node *head)
{
    struct Node *new_head = NULL;
    struct Node *new_tail = NULL;
    const struct Node *current = head;
    int take = 1;

    while (current != NULL) {
        if (take) {
            struct Node *new_node = create_node(current->data);
            if (new_node == NULL) {
                free_list(new_head);
                return NULL;
            }
            if (new_head == NULL) {
                new_head = new_node;
            } else {
                new_tail->next = new_node;
            }
            new_tail = new_node;
        }
        take = !take;
        current = current->next;
    }

    return new_head;
}

void print_list(const struct Node *head)
{
    const struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(struct Node *head)
{
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;
    struct Node *head = NULL;
    struct Node *tail = NULL;
    struct Node *alt_head = NULL;

    for (i = 0; i < count; i++) {
        struct Node *new_node = create_node(values[i]);
        if (new_node == NULL) {
            fprintf(stderr, "Error: memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
        if (head == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    printf("Original list: ");
    print_list(head);

    alt_head = alternate_elements(head);
    if (alt_head == NULL && head != NULL) {
        fprintf(stderr, "Error: failed to create alternate list\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("Alternate elements list: ");
    print_list(alt_head);

    free_list(alt_head);
    free_list(head);

    return EXIT_SUCCESS;
}