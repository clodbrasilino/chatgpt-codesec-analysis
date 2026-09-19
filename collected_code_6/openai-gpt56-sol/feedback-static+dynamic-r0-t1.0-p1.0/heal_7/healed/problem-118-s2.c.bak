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
        size_t length = end != NULL ? (size_t)(end - start) : strlen(start);

        if (length != 0U) {
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

            node->value = malloc(length + 1U);
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
    int first = 1;

    if (putchar('[') == EOF) {
        return -1;
    }

    for (const ListNode *node = head; node != NULL; node = node->next) {
        const unsigned char *p = (const unsigned char *)node->value;

        if (!first && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (putchar('\'') == EOF) {
            return -1;
        }

        while (*p != '\0') {
            if ((*p == '\\' || *p == '\'') && putchar('\\') == EOF) {
                return -1;
            }

            if (putchar((int)*p) == EOF) {
                return -1;
            }

            ++p;
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
    const char *input;
    const char *delimiter;

    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: %s <string> [delimiter]\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    input = argv[1];
    delimiter = argc == 3 ? argv[2] : " ";

    errno = 0;
    list = string_to_list(input, delimiter);

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

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}