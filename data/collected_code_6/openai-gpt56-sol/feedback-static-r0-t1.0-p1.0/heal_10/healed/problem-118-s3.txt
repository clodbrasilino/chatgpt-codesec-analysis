#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringList {
    char *value;
    struct StringList *next;
} StringList;

static void free_string_list(StringList *list)
{
    while (list != NULL) {
        StringList *next = list->next;
        free(list->value);
        free(list);
        list = next;
    }
}

static char *duplicate_range(const char *start, size_t available, size_t length)
{
    char *copy;

    if (start == NULL || length > available) {
        errno = EINVAL;
        return NULL;
    }

    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        memcpy(copy, start, length);
    }

    copy[length] = '\0';
    return copy;
}

static int string_to_list_n(const char *input, size_t input_length,
                            char delimiter, StringList **result)
{
    StringList *head = NULL;
    StringList **tail = &head;
    size_t start = 0;

    if (input == NULL || result == NULL || delimiter == '\0') {
        errno = EINVAL;
        return -1;
    }

    *result = NULL;

    for (;;) {
        const char *segment;
        const char *end;
        size_t remaining;
        size_t length;
        StringList *node;

        if (start > input_length) {
            errno = EINVAL;
            free_string_list(head);
            return -1;
        }

        segment = input + start;
        remaining = input_length - start;
        end = memchr(segment, (unsigned char)delimiter, remaining);
        length = end != NULL ? (size_t)(end - segment) : remaining;

        node = malloc(sizeof(*node));
        if (node == NULL) {
            free_string_list(head);
            return -1;
        }

        node->value = duplicate_range(segment, remaining, length);
        if (node->value == NULL) {
            free(node);
            free_string_list(head);
            return -1;
        }

        node->next = NULL;
        *tail = node;
        tail = &node->next;

        if (end == NULL) {
            break;
        }

        if (length >= remaining || start > SIZE_MAX - length - 1) {
            errno = EOVERFLOW;
            free_string_list(head);
            return -1;
        }

        start += length + 1;
    }

    *result = head;
    return 0;
}

static int bounded_string_length(const char *string, size_t maximum,
                                 size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL) {
        errno = EINVAL;
        return -1;
    }

    terminator = memchr(string, '\0', maximum);
    if (terminator == NULL) {
        errno = EOVERFLOW;
        return -1;
    }

    *length = (size_t)(terminator - string);
    return 0;
}

int main(int argc, char *argv[])
{
    StringList *list = NULL;
    StringList *current;
    size_t input_length;
    char delimiter = ',';

    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: %s <string> [delimiter]\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    if (argv == NULL || argv[1] == NULL) {
        fputs("Invalid input string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (bounded_string_length(argv[1], SIZE_MAX, &input_length) != 0) {
        perror("input string");
        return EXIT_FAILURE;
    }

    if (argc == 3) {
        size_t delimiter_length;

        if (argv[2] == NULL ||
            bounded_string_length(argv[2], 2, &delimiter_length) != 0 ||
            delimiter_length != 1) {
            fputs("Delimiter must be exactly one non-null character.\n",
                  stderr);
            return EXIT_FAILURE;
        }

        delimiter = argv[2][0];
    }

    if (string_to_list_n(argv[1], input_length, delimiter, &list) != 0) {
        perror("string_to_list_n");
        return EXIT_FAILURE;
    }

    for (current = list; current != NULL; current = current->next) {
        if (puts(current->value) == EOF) {
            perror("puts");
            free_string_list(list);
            return EXIT_FAILURE;
        }
    }

    free_string_list(list);

    if (fflush(stdout) == EOF) {
        perror("fflush");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}