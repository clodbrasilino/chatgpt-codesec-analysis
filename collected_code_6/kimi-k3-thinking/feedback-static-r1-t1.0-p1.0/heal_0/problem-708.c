#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

void free_list(Node *head);
Node *string_to_list(const char *str);
void print_list(const Node *head);

void free_list(Node *head)
{
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

Node *string_to_list(const char *str)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    for (i = 0; str[i] != '\0'; i++) {
        Node *new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }
        new_node->data = str[i];
        new_node->next = NULL;

        if (tail == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    return head;
}

void print_list(const Node *head)
{
    while (head != NULL) {
        putchar(head->data);
        if (head->next != NULL) {
            fputs(" -> ", stdout);
        }
        head = head->next;
    }
    putchar('\n');
}

int main(void)
{
    const char *str = "Hello, World!";
    Node *list = string_to_list(str);

    if (list == NULL && *str != '\0') {
        fprintf(stderr, "Error: failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}