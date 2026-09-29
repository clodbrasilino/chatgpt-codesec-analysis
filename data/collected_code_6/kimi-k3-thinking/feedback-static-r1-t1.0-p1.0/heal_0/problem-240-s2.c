#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *create_node(int data)
{
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

static void free_list(Node *head)
{
    Node *next;
    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }
}

static Node *create_list(const int *values, size_t count)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i;

    for (i = 0; i < count; i++) {
        Node *node = create_node(values[i]);
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        if (tail != NULL) {
            tail->next = node;
        } else {
            head = node;
        }
        tail = node;
    }
    return head;
}

static void print_list(const Node *head)
{
    const Node *current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

Node *replace_last_with_list(Node *head, Node *replacement)
{
    Node *current;

    if (head == NULL) {
        return replacement;
    }
    if (head->next == NULL) {
        free(head);
        return replacement;
    }
    current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = replacement;
    return head;
}

int main(void)
{
    int values1[] = {1, 2, 3, 4, 5};
    int values2[] = {10, 20, 30};
    Node *list1 = create_list(values1, sizeof(values1) / sizeof(values1[0]));
    Node *list2;

    if (list1 == NULL) {
        fprintf(stderr, "Error: failed to create first list\n");
        return EXIT_FAILURE;
    }

    list2 = create_list(values2, sizeof(values2) / sizeof(values2[0]));
    if (list2 == NULL) {
        fprintf(stderr, "Error: failed to create second list\n");
        free_list(list1);
        return EXIT_FAILURE;
    }

    printf("Original list: ");
    print_list(list1);

    printf("Replacement list: ");
    print_list(list2);

    list1 = replace_last_with_list(list1, list2);

    printf("Resulting list: ");
    print_list(list1);

    free_list(list1);

    return EXIT_SUCCESS;
}