#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum {
    SINGLE,
    MULTI
} NodeType;

typedef struct Node {
    NodeType type;
    int count;
    char value;
    struct Node *next;
} Node;

static Node *create_node(NodeType type, int count, char value)
{
    Node *node = (Node *)malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->type = type;
    node->count = count;
    node->value = value;
    node->next = NULL;
    return node;
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

Node *encode_modified(const char *data, size_t length)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i = 0;

    if (data == NULL) {
        return NULL;
    }

    while (i < length) {
        size_t run = 1;
        Node *node = NULL;

        while (i + run < length && data[i + run] == data[i]) {
            run++;
        }

        if (run > (size_t)INT_MAX) {
            free_list(head);
            return NULL;
        }

        if (run == 1) {
            node = create_node(SINGLE, 1, data[i]);
        } else {
            node = create_node(MULTI, (int)run, data[i]);
        }

        if (node == NULL) {
            free_list(head);
            return NULL;
        }

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;

        i += run;
    }

    return head;
}

void print_list(const Node *head)
{
    putchar('[');
    while (head != NULL) {
        if (head->type == MULTI) {
            printf("(%d %c)", head->count, head->value);
        } else {
            printf("%c", head->value);
        }
        if (head->next != NULL) {
            putchar(' ');
        }
        head = head->next;
    }
    puts("]");
}

int main(void)
{
    const char data[] = "aaaabccaadeeee";
    Node *encoded = encode_modified(data, sizeof(data) - 1);

    if (encoded == NULL) {
        fprintf(stderr, "Encoding failed.\n");
        return EXIT_FAILURE;
    }

    print_list(encoded);
    free_list(encoded);
    encoded = NULL;

    return EXIT_SUCCESS;
}