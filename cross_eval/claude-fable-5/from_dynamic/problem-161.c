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

static int append(struct Node **head, int value)
{
    struct Node *node;
    struct Node *cur;

    if (head == NULL) {
        return -1;
    }
    node = create_node(value);
    if (node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = node;
        return 0;
    }
    cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
    return 0;
}

static int contains(const struct Node *head, int value)
{
    while (head != NULL) {
        if (head->data == value) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

static void remove_elements(struct Node **head, const struct Node *filter)
{
    struct Node *cur;
    struct Node *prev;

    if (head == NULL) {
        return;
    }
    prev = NULL;
    cur = *head;
    while (cur != NULL) {
        if (contains(filter, cur->data)) {
            struct Node *to_free = cur;
            if (prev == NULL) {
                *head = cur->next;
            } else {
                prev->next = cur->next;
            }
            cur = cur->next;
            free(to_free);
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
}

static void free_list(struct Node **head)
{
    struct Node *cur;

    if (head == NULL) {
        return;
    }
    cur = *head;
    while (cur != NULL) {
        struct Node *next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
}

static void print_list(const struct Node *head)
{
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    struct Node *list = NULL;
    struct Node *filter = NULL;
    int list_values[] = {1, 2, 3, 4, 5, 6, 7};
    int filter_values[] = {2, 4, 6};
    size_t i;

    for (i = 0; i < sizeof(list_values) / sizeof(list_values[0]); i++) {
        if (append(&list, list_values[i]) != 0) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(&list);
            free_list(&filter);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < sizeof(filter_values) / sizeof(filter_values[0]); i++) {
        if (append(&filter, filter_values[i]) != 0) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(&list);
            free_list(&filter);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(list);
    printf("Filter list:   ");
    print_list(filter);

    remove_elements(&list, filter);

    printf("Result list:   ");
    print_list(list);

    free_list(&list);
    free_list(&filter);

    return EXIT_SUCCESS;
}