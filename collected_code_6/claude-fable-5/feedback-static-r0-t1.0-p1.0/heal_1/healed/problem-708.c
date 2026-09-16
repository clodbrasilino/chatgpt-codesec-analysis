#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data;
    struct Node *next;
};

static struct Node *create_node(char c)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = c;
    node->next = NULL;
    return node;
}

static void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

static int string_to_list(const char *str, struct Node **out_head)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;
    size_t i;
    size_t len;

    if (out_head == NULL) {
        return -1;
    }

    *out_head = NULL;

    if (str == NULL) {
        return -1;
    }

    len = strlen(str);
    for (i = 0; i < len; i++) {
        struct Node *node = create_node(str[i]);
        if (node == NULL) {
            free_list(head);
            return -1;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    *out_head = head;
    return 0;
}

static void print_list(const struct Node *head)
{
    const struct Node *cur = head;
    while (cur != NULL) {
        if (printf("%c -> ", cur->data) < 0) {
            return;
        }
        cur = cur->next;
    }
    (void)printf("NULL\n");
}

int main(void)
{
    static const char input[] = "Hello, World!";
    struct Node *list = NULL;

    if (string_to_list(input, &list) != 0) {
        (void)fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}