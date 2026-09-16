#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

static Node *create_node(char ch)
{
    Node *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = ch;
    new_node->next = NULL;

    return new_node;
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

Node *string_to_list(const char *str)
{
    Node *head = NULL;
    Node *tail = NULL;

    if (str == NULL) {
        return NULL;
    }

    while (*str != '\0') {
        Node *new_node = create_node(*str);

        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }

        if (tail == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;

        str++;
    }

    return head;
}

void print_list(const Node *head)
{
    while (head != NULL) {
        printf("%c", head->data);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    putchar('\n');
}

int main(void)
{
    const char *str = "Hello, World!";
    Node *list = string_to_list(str);

    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list.\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", str);
    printf("List:   ");
    print_list(list);

    free_list(list);
    list = NULL;

    return EXIT_SUCCESS;
}