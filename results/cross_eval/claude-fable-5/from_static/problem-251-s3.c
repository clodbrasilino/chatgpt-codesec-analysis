#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

static struct Node *create_node(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->next = NULL;
    return node;
}

static void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

static int insert_before_each(struct Node **head, int value)
{
    struct Node *current;
    struct Node *prev;

    if (head == NULL) {
        return -1;
    }

    prev = NULL;
    current = *head;

    while (current != NULL) {
        struct Node *new_node = create_node(value);
        if (new_node == NULL) {
            return -1;
        }
        new_node->next = current;
        if (prev == NULL) {
            *head = new_node;
        } else {
            prev->next = new_node;
        }
        prev = current;
        current = current->next;
    }

    return 0;
}

static int append(struct Node **head, int value)
{
    struct Node *new_node;
    struct Node *current;

    if (head == NULL) {
        return -1;
    }

    new_node = create_node(value);
    if (new_node == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = new_node;
        return 0;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return 0;
}

static void print_list(const struct Node *head)
{
    const struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void)
{
    struct Node *head = NULL;
    int values[] = {1, 2, 3, 4};
    size_t i;
    size_t count = sizeof(values) / sizeof(values[0]);

    for (i = 0; i < count; i++) {
        if (append(&head, values[i]) != 0) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    if (insert_before_each(&head, 0) != 0) {
        fprintf(stderr, "Insertion failed\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("Modified list: ");
    print_list(head);

    free_list(head);
    return EXIT_SUCCESS;
}