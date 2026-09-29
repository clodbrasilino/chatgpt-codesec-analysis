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

    for (size_t i = 0; i < length; ++i) {
        copy[i] = start[i];
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

    node = malloc(sizeof *node);
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

static int string_to_list_n(const char *input, size_t input_length,
                            char delimiter, StringNode **result)
{
    StringNode *head = NULL;
    StringNode *tail = NULL;
    size_t token_start = 0;

    if (input == NULL || result == NULL || delimiter == '\0') {
        errno = EINVAL;
        return -1;
    }

    *result = NULL;

    for (size_t cursor = 0; cursor < input_length; ++cursor) {
        if (input[cursor] == delimiter) {
            if (append_node(&head, &tail, input + token_start,
                            cursor - token_start) != 0) {
                free_list(head);
                return -1;
            }

            token_start = cursor + 1;
        }
    }

    if (append_node(&head, &tail, input + token_start,
                    input_length - token_start) != 0) {
        free_list(head);
        return -1;
    }

    *result = head;
    return 0;
}

static int print_list(const StringNode *head)
{
    for (const StringNode *node = head; node != NULL; node = node->next) {
        if (fputs(node->value, stdout) == EOF ||
            fputc('\n', stdout) == EOF) {
            return -1;
        }
    }

    return 0;
}

static int bounded_string_length(const char *string, size_t maximum,
                                 size_t *length)
{
    size_t i;

    if (string == NULL || length == NULL) {
        errno = EINVAL;
        return -1;
    }

    for (i = 0; i < maximum; ++i) {
        if (string[i] == '\0') {
            *length = i;
            return 0;
        }
    }

    errno = EOVERFLOW;
    return -1;
}

int main(int argc, char *argv[])
{
    StringNode *list = NULL;
    char delimiter = ',';
    size_t input_length;

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <string> [delimiter]\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (argv == NULL || argv[1] == NULL) {
        fputs("Invalid argument vector.\n", stderr);
        return EXIT_FAILURE;
    }

    if (argc == 3) {
        if (argv[2] == NULL || argv[2][0] == '\0' ||
            argv[2][1] != '\0') {
            fputs("Delimiter must be exactly one non-null character.\n",
                  stderr);
            return EXIT_FAILURE;
        }

        delimiter = argv[2][0];
    }

    if (bounded_string_length(argv[1], SIZE_MAX, &input_length) != 0) {
        perror("input");
        return EXIT_FAILURE;
    }

    if (string_to_list_n(argv[1], input_length, delimiter, &list) != 0) {
        perror("string_to_list_n");
        return EXIT_FAILURE;
    }

    if (print_list(list) != 0) {
        perror("print_list");
        free_list(list);
        return EXIT_FAILURE;
    }

    free_list(list);

    if (fflush(stdout) == EOF) {
        perror("stdout");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}