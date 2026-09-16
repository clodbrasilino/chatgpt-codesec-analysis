#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *value;
    struct ListNode *next;
} ListNode;

static void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head->value);
        free(head);
        head = next;
    }
}

static ListNode *string_to_list(const char *input, const char *delimiter)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    char *copy;
    char *token;
    char *saveptr = NULL;

    if (input == NULL || delimiter == NULL || delimiter[0] == '\0') {
        errno = EINVAL;
        return NULL;
    }

    copy = strdup(input);
    if (copy == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (token = strtok_r(copy, delimiter, &saveptr);
         token != NULL;
         token = strtok_r(NULL, delimiter, &saveptr)) {
        ListNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            free(copy);
            free_list(head);
            errno = ENOMEM;
            return NULL;
        }

        node->value = strdup(token);
        if (node->value == NULL) {
            free(node);
            free(copy);
            free_list(head);
            errno = ENOMEM;
            return NULL;
        }

        node->next = NULL;

        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    free(copy);
    errno = 0;
    return head;
}

static int print_list(const ListNode *head)
{
    const ListNode *node;
    int first = 1;

    if (putchar('[') == EOF) {
        return -1;
    }

    for (node = head; node != NULL; node = node->next) {
        if (!first && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('\'') == EOF ||
            fputs(node->value, stdout) == EOF ||
            putchar('\'') == EOF) {
            return -1;
        }

        first = 0;
    }

    return puts("]") == EOF ? -1 : 0;
}

int main(int argc, char *argv[])
{
    ListNode *list;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <delimiters>\n",
                argc > 0 ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    errno = 0;
    list = string_to_list(argv[1], argv[2]);

    if (list == NULL && errno != 0) {
        perror("string_to_list");
        return EXIT_FAILURE;
    }

    if (print_list(list) != 0) {
        free_list(list);
        fprintf(stderr, "Failed to write output\n");
        return EXIT_FAILURE;
    }

    free_list(list);
    return EXIT_SUCCESS;
}