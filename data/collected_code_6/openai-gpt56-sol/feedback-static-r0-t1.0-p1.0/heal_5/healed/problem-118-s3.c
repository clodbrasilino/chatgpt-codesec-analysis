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

static char *duplicate_range(const char *start, size_t length)
{
    char *copy;

    if (start == NULL) {
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

    if (length > 0) {
        memcpy(copy, start, length);
    }

    copy[length] = '\0';
    return copy;
}

static int string_to_list(const char *input, char delimiter, StringList **result)
{
    StringList *head = NULL;
    StringList **tail = &head;
    const char *start;
    const char *input_end;

    if (input == NULL || result == NULL || delimiter == '\0') {
        errno = EINVAL;
        return -1;
    }

    *result = NULL;
    input_end = input + strlen(input);
    start = input;

    for (;;) {
        const char *end = memchr(start, (unsigned char)delimiter,
                                 (size_t)(input_end - start));
        size_t length = end != NULL
                            ? (size_t)(end - start)
                            : (size_t)(input_end - start);
        StringList *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_string_list(head);
            return -1;
        }

        node->value = duplicate_range(start, length);
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

        start = end + 1;
    }

    *result = head;
    return 0;
}

int main(int argc, char *argv[])
{
    StringList *list = NULL;
    StringList *current;
    char delimiter = ',';

    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: %s <string> [delimiter]\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL) {
        fputs("Invalid input string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (argc == 3) {
        if (argv[2] == NULL || argv[2][0] == '\0' || argv[2][1] != '\0') {
            fputs("Delimiter must be exactly one non-null character.\n", stderr);
            return EXIT_FAILURE;
        }

        delimiter = argv[2][0];
    }

    if (string_to_list(argv[1], delimiter, &list) != 0) {
        perror("string_to_list");
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