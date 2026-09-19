#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {
    char *data;
    struct node *next;
};

static struct node *create_node(const char *start, size_t len)
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
    memcpy(n->data, start, len);
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

static int string_to_list(const char *str, struct node **out)
{
    struct node *head = NULL;
    struct node *tail = NULL;
    size_t i = 0;

    if (str == NULL || out == NULL) {
        return -1;
    }

    *out = NULL;

    while (str[i] != '\0') {
        size_t start;
        size_t len;
        struct node *n;

        while (str[i] != '\0' && isspace((unsigned char)str[i])) {
            i++;
        }
        if (str[i] == '\0') {
            break;
        }

        start = i;
        while (str[i] != '\0' && !isspace((unsigned char)str[i])) {
            i++;
        }
        len = i - start;

        n = create_node(&str[start], len);
        if (n == NULL) {
            free_list(head);
            return -1;
        }

        if (head == NULL) {
            head = n;
            tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
    }

    *out = head;
    return 0;
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
    (void)printf("]\n");
}

int main(void)
{
    const char *input = "python programming";
    struct node *list = NULL;

    if (string_to_list(input, &list) != 0) {
        (void)fprintf(stderr, "Failed to build list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}