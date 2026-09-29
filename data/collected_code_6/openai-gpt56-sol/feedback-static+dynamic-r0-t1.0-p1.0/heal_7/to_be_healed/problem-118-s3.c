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

    if (start == NULL || length > available || length == SIZE_MAX) {
        errno = EINVAL;
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

static int string_to_list_n(const char *input, size_t input_length,
                            unsigned char delimiter, StringList **result)
{
    StringList *head = NULL;
    StringList **tail = &head;
    size_t offset = 0;

    if (input == NULL || result == NULL || delimiter == '\0') {
        errno = EINVAL;
        return -1;
    }

    *result = NULL;

    for (;;) {
        const char *start;
        const char *end;
        size_t remaining;
        size_t length;
        StringList *node;

        if (offset > input_length) {
            errno = EINVAL;
            free_string_list(head);
            return -1;
        }

        start = input + offset;
        remaining = input_length - offset;
        end = memchr(start, delimiter, remaining);
        length = end != NULL ? (size_t)(end - start) : remaining;

        node = malloc(sizeof(*node));
        if (node == NULL) {
            free_string_list(head);
            return -1;
        }

        node->value = duplicate_range(start, remaining, length);
        node->next = NULL;

        if (node->value == NULL) {
            free(node);
            free_string_list(head);
            return -1;
        }

        *tail = node;
        tail = &node->next;

        if (end == NULL) {
            break;
        }

        if (length == SIZE_MAX || offset > input_length - (length + 1)) {
            errno = EINVAL;
            free_string_list(head);
            return -1;
        }

        offset += length + 1;
    }

    *result = head;
    return 0;
}

int main(int argc, char *argv[])
{
    StringList *list = NULL;
    StringList *current;
    unsigned char delimiter = ',';
    const char *input;
    size_t input_length;

    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: %s <string> [delimiter]\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    if (argv == NULL || argv[1] == NULL) {
        fputs("Input string is missing.\n", stderr);
        return EXIT_FAILURE;
    }

    input = argv[1];

    if (argc == 3) {
        if (argv[2] == NULL || argv[2][0] == '\0' || argv[2][1] != '\0') {
            fputs("Delimiter must be exactly one non-null character.\n", stderr);
            return EXIT_FAILURE;
        }

        delimiter = (unsigned char)argv[2][0];
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    if (string_to_list_n(input, input_length, delimiter, &list) != 0) {
        perror("string_to_list_n");
        return EXIT_FAILURE;
    }

    for (current = list; current != NULL; current = current->next) {
        if (fputs(current->value, stdout) == EOF ||
            fputc('\n', stdout) == EOF) {
            perror("stdout");
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