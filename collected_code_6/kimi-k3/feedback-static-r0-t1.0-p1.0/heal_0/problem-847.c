#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} SingletonTuple;

Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node *copy_list_from_singleton(const SingletonTuple *tuple)
{
    if (tuple == NULL || tuple->head == NULL) {
        return NULL;
    }

    Node *new_head = NULL;
    Node *new_tail = NULL;
    Node *current = tuple->head;

    while (current != NULL) {
        Node *new_node = create_node(current->data);
        if (new_node == NULL) {
            while (new_head != NULL) {
                Node *temp = new_head;
                new_head = new_head->next;
                free(temp);
            }
            return NULL;
        }

        if (new_head == NULL) {
            new_head = new_node;
            new_tail = new_node;
        } else {
            new_tail->next = new_node;
            new_tail = new_node;
        }

        current = current->next;
    }

    return new_head;
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

void print_list(const Node *head)
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
    SingletonTuple tuple = {NULL};
    
    tuple.head = create_node(1);
    if (tuple.head == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    Node *current = tuple.head;
    for (int i = 2; i <= 5; i++) {
        current->next = create_node(i);
        if (current->next == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(tuple.head);
            return EXIT_FAILURE;
        }
        current = current->next;
    }

    printf("Original list: ");
    print_list(tuple.head);

    Node *copied_list = copy_list_from_singleton(&tuple);
    if (copied_list == NULL) {
        fprintf(stderr, "Failed to copy list\n");
        free_list(tuple.head);
        return EXIT_FAILURE;
    }

    printf("Copied list:   ");
    print_list(copied_list);

    free_list(tuple.head);
    free_list(copied_list);

    return EXIT_SUCCESS;
}