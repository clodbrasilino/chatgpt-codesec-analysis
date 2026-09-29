#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringNode {
    char *value;
    struct StringNode *next;
} StringNode;

static void free_list(StringNode *head)
{
    while (head != NULL) {
        StringNode *next = head->next;
        free(head->value);
        free(head);
        head = next;
    }
}

static char *duplicate_range(const char *start, size_t length)
{
    char *copy;

    if (start == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (length > SIZE_MAX - 1) {
        errno = ENOMEM;
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, start, length);
    }

    copy[length] = '\0';
    return copy;
}

static int append_node(StringNode **head, StringNode **tail,
                       const char *start, size_t length)
{
    StringNode *node;

    if (head == NULL || tail == NULL || start == NULL) {
        errno = EINVAL;
        return -1;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return -1;
    }

    node->value = duplicate_range(start, length);
    if (node->value == NULL) {
        free(node);
        return -1;
    }

    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 0;
}

static int string_to_list(const char *input, char delimiter,
                          StringNode **result)
{
    StringNode *head = NULL;
    StringNode *tail = NULL;
    const char *token_start;
    const char *cursor;

    if (input == NULL || result == NULL || delimiter == '\0') {
        errno = EINVAL;
        return -1;
    }

    *result = NULL;
    token_start = input;
    cursor = input;

    for (;;) {
        const char *separator = strchr(cursor, delimiter);
        const char *end = separator != NULL
                              ? separator
                              /* Possible weaknesses found:
                               * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                               */
                              : cursor + strlen(cursor);
        size_t length = (size_t)(end - token_start);

        if (append_node(&head, &tail, token_start, length) != 0) {
            int saved_errno = errno;
            free_list(head);
            errno = saved_errno;
            return -1;
        }

        if (separator == NULL) {
            break;
        }

        cursor = separator + 1;
        token_start = cursor;
    }

    *result = head;
    return 0;
}

static int print_list(const StringNode *head)
{
    const StringNode *node;

    for (node = head; node != NULL; node = node->next) {
        if (fputs(node->value, stdout) == EOF ||
            fputc('\n', stdout) == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    StringNode *list = NULL;
    char delimiter = ',';

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <string> [delimiter]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argc == 3) {
        if (argv[2][0] == '\0' || argv[2][1] != '\0') {
            fputs("Delimiter must be exactly one non-null character.\n",
                  stderr);
            return EXIT_FAILURE;
        }

        delimiter = argv[2][0];
    }

    if (string_to_list(argv[1], delimiter, &list) != 0) {
        perror("string_to_list");
        return EXIT_FAILURE;
    }

    if (print_list(list) != 0) {
        int saved_errno = errno;
        free_list(list);
        errno = saved_errno;
        perror("print_list");
        return EXIT_FAILURE;
    }

    free_list(list);

    if (fflush(stdout) == EOF) {
        perror("fflush");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}