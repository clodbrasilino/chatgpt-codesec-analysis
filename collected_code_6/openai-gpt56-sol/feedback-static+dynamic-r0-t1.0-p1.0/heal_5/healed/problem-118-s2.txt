#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdint.h>
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
    const char *start;
    size_t delimiter_length;

    if (input == NULL || delimiter == NULL || delimiter[0] == '\0') {
        errno = EINVAL;
        return NULL;
    }

    delimiter_length = strlen(delimiter);
    start = input;

    for (;;) {
        const char *end = strstr(start, delimiter);
        size_t length = end != NULL
                            ? (size_t)(end - start)
                            : strlen(start);

        if (length != 0) {
            ListNode *node;

            if (length == SIZE_MAX) {
                free_list(head);
                errno = ENOMEM;
                return NULL;
            }

            node = malloc(sizeof(*node));
            if (node == NULL) {
                free_list(head);
                errno = ENOMEM;
                return NULL;
            }

            node->value = malloc(length + 1);
            if (node->value == NULL) {
                free(node);
                free_list(head);
                errno = ENOMEM;
                return NULL;
            }

            memcpy(node->value, start, length);
            node->value[length] = '\0';
            node->next = NULL;

            if (tail == NULL) {
                head = node;
            } else {
                tail->next = node;
            }

            tail = node;
        }

        if (end == NULL) {
            break;
        }

        start = end + delimiter_length;
    }

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
        const unsigned char *p;

        if (!first && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('\'') == EOF) {
            return -1;
        }

        for (p = (const unsigned char *)node->value; *p != '\0'; ++p) {
            if ((*p == '\\' || *p == '\'') && putchar('\\') == EOF) {
                return -1;
            }

            if (putchar((int)*p) == EOF) {
                return -1;
            }
        }

        if (putchar('\'') == EOF) {
            return -1;
        }

        first = 0;
    }

    return puts("]") == EOF ? -1 : 0;
}

int main(int argc, char *const argv[])
{
    ListNode *list;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <delimiter>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
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
        fputs("Failed to write output\n", stderr);
        return EXIT_FAILURE;
    }

    free_list(list);
    return EXIT_SUCCESS;
}