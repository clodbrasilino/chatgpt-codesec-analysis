#include <errno.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringList {
    char *value;
    struct StringList *next;
} StringList;

static void free_string_list(StringList *head)
{
    while (head != NULL) {
        StringList *next = head->next;
        free(head->value);
        free(head);
        head = next;
    }
}

static int duplicate_range(const char *start, size_t available,
                           size_t length, char **result)
{
    char *copy;

    if (start == NULL || result == NULL) {
        return EINVAL;
    }

    *result = NULL;

    if (length > available) {
        return EINVAL;
    }

    if (length > SIZE_MAX - 1) {
        return EOVERFLOW;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return ENOMEM;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, start, length);
    }

    copy[length] = '\0';
    *result = copy;
    return 0;
}

static int append_range(StringList **head, StringList **tail,
                        const char *start, size_t available, size_t length)
{
    StringList *node;
    int status;

    if (head == NULL || tail == NULL || start == NULL) {
        return EINVAL;
    }

    if ((*head == NULL) != (*tail == NULL)) {
        return EINVAL;
    }

    node = malloc(sizeof *node);
    if (node == NULL) {
        return ENOMEM;
    }

    node->value = NULL;
    node->next = NULL;

    status = duplicate_range(start, available, length, &node->value);
    if (status != 0) {
        free(node);
        return status;
    }

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 0;
}

static int string_to_list_n(const char *input, size_t input_size,
                            char delimiter, StringList **result)
{
    const char *end;
    const char *start;
    StringList *head = NULL;
    StringList *tail = NULL;

    if (input == NULL || result == NULL || delimiter == '\0') {
        return EINVAL;
    }

    *result = NULL;

    end = memchr(input, '\0', input_size);
    if (end == NULL) {
        return EINVAL;
    }

    start = input;

    for (;;) {
        size_t available = (size_t)(end - start);
        const char *separator;
        const char *field_end;
        size_t length;
        int status;

        separator = memchr(start, (unsigned char)delimiter, available);
        field_end = separator != NULL ? separator : end;
        length = (size_t)(field_end - start);

        status = append_range(&head, &tail, start, available, length);
        if (status != 0) {
            free_string_list(head);
            return status;
        }

        if (separator == NULL) {
            break;
        }

        start = separator + 1;
    }

    *result = head;
    return 0;
}

int main(void)
{
    static const char input[] = "alpha,beta,gamma,delta";
    StringList *list = NULL;
    StringList *current;
    int status;

    status = string_to_list_n(input, sizeof input, ',', &list);
    if (status != 0) {
        fprintf(stderr, "Failed to convert string to list: %s\n",
                strerror(status));
        return EXIT_FAILURE;
    }

    for (current = list; current != NULL; current = current->next) {
        if (puts(current->value) == EOF) {
            free_string_list(list);
            return EXIT_FAILURE;
        }
    }

    free_string_list(list);
    return EXIT_SUCCESS;
}