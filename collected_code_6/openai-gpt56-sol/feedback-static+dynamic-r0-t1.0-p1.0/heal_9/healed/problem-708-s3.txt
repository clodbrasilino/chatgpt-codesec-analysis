#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringNode {
    char *value;
    size_t length;
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

    if (length == SIZE_MAX) {
        errno = ENOMEM;
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
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

    node->length = length;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 0;
}

static int string_to_list_bounded(const char *input, size_t input_length,
                                  char delimiter, StringNode **result)
{
    StringNode *head = NULL;
    StringNode *tail = NULL;
    size_t token_start = 0;
    size_t position;

    if (input == NULL || result == NULL || delimiter == '\0') {
        errno = EINVAL;
        return -1;
    }

    *result = NULL;

    for (position = 0; position < input_length; ++position) {
        if (input[position] == delimiter) {
            if (append_node(&head, &tail, input + token_start,
                            position - token_start) != 0) {
                int saved_errno = errno;
                free_list(head);
                errno = saved_errno;
                return -1;
            }

            token_start = position + 1;
        }
    }

    if (append_node(&head, &tail, input + token_start,
                    input_length - token_start) != 0) {
        int saved_errno = errno;
        free_list(head);
        errno = saved_errno;
        return -1;
    }

    *result = head;
    return 0;
}

static int print_list(const StringNode *head)
{
    const StringNode *node;

    for (node = head; node != NULL; node = node->next) {
        if (node->value == NULL) {
            errno = EINVAL;
            return -1;
        }

        if (node->length > 0 &&
            fwrite(node->value, 1, node->length, stdout) != node->length) {
            return -1;
        }

        if (fputc('\n', stdout) == EOF) {
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    StringNode *list = NULL;
    const char *terminator;
    char delimiter = ',';
    size_t input_length;

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <string> [delimiter]\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL) {
        fputs("Input string is invalid.\n", stderr);
        return EXIT_FAILURE;
    }

    if (argc == 3) {
        if (argv[2] == NULL || argv[2][0] == '\0' || argv[2][1] != '\0') {
            fputs("Delimiter must be exactly one non-null character.\n",
                  stderr);
            return EXIT_FAILURE;
        }

        delimiter = argv[2][0];
    }

    terminator = strchr(argv[1], '\0');
    if (terminator == NULL) {
        fputs("Input string is not null-terminated.\n", stderr);
        return EXIT_FAILURE;
    }

    input_length = (size_t)(terminator - argv[1]);

    if (string_to_list_bounded(argv[1], input_length, delimiter, &list) != 0) {
        perror("string_to_list_bounded");
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