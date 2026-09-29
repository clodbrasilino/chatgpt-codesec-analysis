#include <errno.h>
#include <stddef.h>
#include <stdint.h>
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

static int duplicate_range(const char *start, size_t length, char **result)
{
    char *copy;

    if (start == NULL || result == NULL) {
        return EINVAL;
    }

    *result = NULL;

    if (length > SIZE_MAX - 1) {
        return EOVERFLOW;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return ENOMEM;
    }

    if (length != 0) {
        memcpy(copy, start, length);
    }

    copy[length] = '\0';
    *result = copy;

    return 0;
}

static int append_range(StringList **head, StringList **tail,
                        const char *start, size_t length)
{
    StringList *node;
    int status;

    if (head == NULL || tail == NULL || start == NULL) {
        return EINVAL;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return ENOMEM;
    }

    node->value = NULL;
    node->next = NULL;

    status = duplicate_range(start, length, &node->value);
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

static int string_to_list(const char *input, char delimiter,
                          StringList **result)
{
    const char *start;
    const char *current;
    StringList *head = NULL;
    StringList *tail = NULL;

    if (input == NULL || result == NULL || delimiter == '\0') {
        return EINVAL;
    }

    *result = NULL;
    start = input;

    for (current = input;; ++current) {
        if (*current == delimiter || *current == '\0') {
            size_t length = (size_t)(current - start);
            int status = append_range(&head, &tail, start, length);

            if (status != 0) {
                free_string_list(head);
                return status;
            }

            if (*current == '\0') {
                break;
            }

            start = current + 1;
        }
    }

    *result = head;
    return 0;
}

int main(void)
{
    const char *input = "alpha,beta,gamma,delta";
    StringList *list = NULL;
    StringList *current;
    int status;

    status = string_to_list(input, ',', &list);
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