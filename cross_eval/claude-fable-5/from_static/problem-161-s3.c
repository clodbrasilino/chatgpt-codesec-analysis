#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->next = NULL;
    return node;
}

struct Node *append(struct Node *head, int value)
{
    struct Node *node = create_node(value);
    if (head == NULL) {
        return node;
    }
    struct Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return head;
}

int contains(const struct Node *head, int value)
{
    const struct Node *current = head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

struct Node *remove_elements(struct Node *head, const struct Node *filter)
{
    struct Node *current = head;
    struct Node *prev = NULL;

    while (current != NULL) {
        if (contains(filter, current->data)) {
            struct Node *to_delete = current;
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(to_delete);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return head;
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
    struct Node *list = NULL;
    struct Node *filter = NULL;

    list = append(list, 1);
    list = append(list, 2);
    list = append(list, 3);
    list = append(list, 4);
    list = append(list, 5);
    list = append(list, 6);

    filter = append(filter, 2);
    filter = append(filter, 4);
    filter = append(filter, 6);

    printf("Original list: ");
    print_list(list);

    printf("Filter list: ");
    print_list(filter);

    list = remove_elements(list, filter);

    printf("Result list: ");
    print_list(list);

    free_list(list);
    free_list(filter);

    return EXIT_SUCCESS;
}