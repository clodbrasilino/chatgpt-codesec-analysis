#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static size_t list_length(const Node *head)
{
    size_t length = 0u;
    const Node *current = head;

    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}

static Node *find_max_length_list(Node *const *lists, size_t count)
{
    Node *max_list;
    size_t max_length;
    size_t i;

    if ((lists == NULL) || (count == 0u)) {
        return NULL;
    }

    max_list = lists[0];
    max_length = list_length(lists[0]);

    for (i = 1u; i < count; i++) {
        const size_t current_length = list_length(lists[i]);
        if (current_length > max_length) {
            max_length = current_length;
            max_list = lists[i];
        }
    }

    return max_list;
}

static int append_node(Node **head, int data)
{
    Node *new_node;
    Node *current;

    if (head == NULL) {
        return -1;
    }

    new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return -1;
    }

    new_node->data = data;
    new_node->next = NULL;

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

static void free_list(Node *head)
{
    Node *current = head;

    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
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

int main(void)
{
    enum { LIST_COUNT = 3 };
    Node *lists[LIST_COUNT] = {NULL, NULL, NULL};
    Node *max_list;
    int ok = 1;
    int i;

    if ((append_node(&lists[0], 10) != 0) ||
        (append_node(&lists[0], 20) != 0)) {
        ok = 0;
    }

    if ((append_node(&lists[1], 30) != 0) ||
        (append_node(&lists[1], 40) != 0) ||
        (append_node(&lists[1], 50) != 0) ||
        (append_node(&lists[1], 60) != 0)) {
        ok = 0;
    }

    if ((append_node(&lists[2], 70) != 0) ||
        (append_node(&lists[2], 80) != 0) ||
        (append_node(&lists[2], 90) != 0)) {
        ok = 0;
    }

    if (ok == 0) {
        fprintf(stderr, "Error: memory allocation failed\n");
        for (i = 0; i < LIST_COUNT; i++) {
            free_list(lists[i]);
            lists[i] = NULL;
        }
        return EXIT_FAILURE;
    }

    max_list = find_max_length_list(lists, (size_t)LIST_COUNT);

    if (max_list != NULL) {
        printf("List with maximum length (%zu elements):\n",
               list_length(max_list));
        print_list(max_list);
    } else {
        printf("No lists available\n");
    }

    for (i = 0; i < LIST_COUNT; i++) {
        free_list(lists[i]);
        lists[i] = NULL;
    }

    return EXIT_SUCCESS;
}