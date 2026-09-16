#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef void (*MapFunc)(int);

Node *list_create(const int *values, size_t count);
void list_map(const Node *head, MapFunc func);
void list_free(Node *head);
void print_element(int value);
void print_list_n_times(const Node *head, unsigned int n);

Node *list_create(const int *values, size_t count)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i;

    if (values == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        Node *node = malloc(sizeof(Node));
        if (node == NULL) {
            list_free(head);
            return NULL;
        }
        node->value = values[i];
        node->next = NULL;
        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }
    return head;
}

void list_map(const Node *head, MapFunc func)
{
    const Node *current = head;

    if (func == NULL) {
        return;
    }

    while (current != NULL) {
        func(current->value);
        current = current->next;
    }
}

void list_free(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

void print_element(int value)
{
    if (printf("%d ", value) < 0) {
        exit(EXIT_FAILURE);
    }
}

void print_list_n_times(const Node *head, unsigned int n)
{
    unsigned int i;

    for (i = 0U; i < n; i++) {
        list_map(head, print_element);
        if (printf("\n") < 0) {
            exit(EXIT_FAILURE);
        }
    }
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5};
    const size_t count = sizeof(values) / sizeof(values[0]);
    const unsigned int n = 3U;
    Node *head;

    head = list_create(values, count);
    if (head == NULL) {
        (void)fprintf(stderr, "Failed to create list\n");
        return EXIT_FAILURE;
    }

    print_list_n_times(head, n);
    list_free(head);

    return EXIT_SUCCESS;
}