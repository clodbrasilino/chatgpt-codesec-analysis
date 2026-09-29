#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

static int append_node(Node **head, int data)
{
    Node *new_node;
    Node *current;

    if (head == NULL) {
        return -1;
    }

    new_node = create_node(data);
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

static void swap_first_last(Node *head)
{
    Node *last;
    int temp;

    if (head == NULL || head->next == NULL) {
        return;
    }

    last = head;
    while (last->next != NULL) {
        last = last->next;
    }

    temp = head->data;
    head->data = last->data;
    last->data = temp;
}

static void print_list(const Node *head)
{
    if (head == NULL) {
        printf("(empty)\n");
        return;
    }
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

static void free_list(Node *head)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void)
{
    Node *head = NULL;
    int values[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        if (append_node(&head, values[i]) != 0) {
            fprintf(stderr, "Error: memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    swap_first_last(head);

    printf("After swap:    ");
    print_list(head);

    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}