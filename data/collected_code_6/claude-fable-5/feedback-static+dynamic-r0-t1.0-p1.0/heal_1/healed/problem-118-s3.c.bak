#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *data;
    struct node *next;
};

static struct node *create_node(const char *word, size_t len)
{
    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }
    n->data = malloc(len + 1);
    if (n->data == NULL) {
        free(n);
        return NULL;
    }
    memcpy(n->data, word, len);
    n->data[len] = '\0';
    n->next = NULL;
    return n;
}

static void free_list(struct node *head)
{
    while (head != NULL) {
        struct node *tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

static struct node *string_to_list(const char *str)
{
    struct node *head = NULL;
    struct node *tail = NULL;
    size_t i = 0;
    size_t len;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);

    while (i < len) {
        size_t start;

        while (i < len && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')) {
            i++;
        }
        if (i >= len) {
            break;
        }
        start = i;
        while (i < len && str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            i++;
        }

        {
            struct node *n = create_node(&str[start], i - start);
            if (n == NULL) {
                free_list(head);
                return NULL;
            }
            if (head == NULL) {
                head = n;
                tail = n;
            } else {
                tail->next = n;
                tail = n;
            }
        }
    }

    return head;
}

static void print_list(const struct node *head)
{
    const struct node *cur = head;

    if (printf("[") < 0) {
        return;
    }
    while (cur != NULL) {
        if (printf("'%s'", cur->data) < 0) {
            return;
        }
        if (cur->next != NULL) {
            if (printf(", ") < 0) {
                return;
            }
        }
        cur = cur->next;
    }
    if (printf("]\n") < 0) {
        return;
    }
}

int main(void)
{
    char input[4096];
    struct node *list;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    list = string_to_list(input);

    if (list == NULL && input[0] != '\0') {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}