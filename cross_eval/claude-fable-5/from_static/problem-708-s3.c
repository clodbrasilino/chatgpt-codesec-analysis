#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

struct Node {
    char data;
    struct Node *next;
};

struct Node *create_node(char c)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = c;
    node->next = NULL;
    return node;
}

void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

struct Node *string_to_list(const char *str)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;
    size_t i;
    size_t len;

    if (str == NULL) {
        return NULL;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        struct Node *node = create_node(str[i]);
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

void print_list(const struct Node *head)
{
    const struct Node *current = head;
    while (current != NULL) {
        if (printf("%c -> ", current->data) < 0) {
            return;
        }
        current = current->next;
    }
    (void)printf("NULL\n");
}

int main(void)
{
    const char *input = "Hello, World!";
    struct Node *list = string_to_list(input);

    if (list == NULL) {
        (void)fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}