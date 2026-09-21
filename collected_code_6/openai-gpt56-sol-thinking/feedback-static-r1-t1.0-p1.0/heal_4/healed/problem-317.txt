#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    long value;
    struct ListNode *next;
} ListNode;

typedef struct EncodedNode {
    long value;
    size_t count;
    struct EncodedNode *next;
} EncodedNode;

static void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
}

static void free_encoded_list(EncodedNode *head)
{
    while (head != NULL) {
        EncodedNode *next = head->next;
        free(head);
        head = next;
    }
}

static bool append_value(ListNode **head, ListNode **tail, long value)
{
    if (head == NULL || tail == NULL) {
        return false;
    }

    ListNode *node = malloc(sizeof *node);
    if (node == NULL) {
        return false;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return true;
}

static bool parse_long(const char *text, long *value)
{
    char *end = NULL;
    long parsed_value;

    if (text == NULL || value == NULL) {
        return false;
    }

    errno = 0;
    parsed_value = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return false;
    }

    *value = parsed_value;
    return true;
}

static bool modified_run_length_encode(
    const ListNode *head,
    EncodedNode **encoded_head)
{
    EncodedNode *result = NULL;
    EncodedNode *tail = NULL;

    if (encoded_head == NULL) {
        return false;
    }

    *encoded_head = NULL;

    while (head != NULL) {
        const long value = head->value;
        size_t count = 0;

        do {
            if (count == SIZE_MAX) {
                free_encoded_list(result);
                return false;
            }

            ++count;
            head = head->next;
        } while (head != NULL && head->value == value);

        EncodedNode *node = malloc(sizeof *node);
        if (node == NULL) {
            free_encoded_list(result);
            return false;
        }

        node->value = value;
        node->count = count;
        node->next = NULL;

        if (tail == NULL) {
            result = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    *encoded_head = result;
    return true;
}

static bool print_encoded_list(const EncodedNode *head)
{
    bool first = true;

    if (fputc('[', stdout) == EOF) {
        return false;
    }

    while (head != NULL) {
        int result;

        if (!first && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (head->count == 1) {
            result = printf("%ld", head->value);
        } else {
            result = printf("(%zu %ld)", head->count, head->value);
        }

        if (result < 0) {
            return false;
        }

        first = false;
        head = head->next;
    }

    return fputs("]\n", stdout) != EOF;
}

int main(int argc, char *argv[])
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    EncodedNode *encoded = NULL;
    int exit_status = EXIT_SUCCESS;

    for (int i = 1; i < argc; ++i) {
        const char *const argument = argv[i];
        long value;

        if (!parse_long(argument, &value)) {
            fprintf(stderr, "Invalid integer: %s\n", argument);
            free_list(head);
            return EXIT_FAILURE;
        }

        if (!append_value(&head, &tail, value)) {
            fputs("Failed to allocate input list\n", stderr);
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (!modified_run_length_encode(head, &encoded)) {
        fputs("Failed to encode list\n", stderr);
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!print_encoded_list(encoded)) {
        fputs("Failed to write output\n", stderr);
        exit_status = EXIT_FAILURE;
    }

    free_encoded_list(encoded);
    free_list(head);

    return exit_status;
}