#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
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
    ListNode *node;

    if (head == NULL || tail == NULL) {
        return false;
    }

    node = malloc(sizeof(*node));
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

static EncodedNode *modified_run_length_encode(const ListNode *head)
{
    EncodedNode *result = NULL;
    EncodedNode *tail = NULL;

    while (head != NULL) {
        const long value = head->value;
        size_t count = 0;
        EncodedNode *node;

        do {
            if (count == SIZE_MAX) {
                free_encoded_list(result);
                return NULL;
            }

            ++count;
            head = head->next;
        } while (head != NULL && head->value == value);

        node = malloc(sizeof(*node));
        if (node == NULL) {
            free_encoded_list(result);
            return NULL;
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

    return result;
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    EncodedNode *encoded;
    int exit_status = EXIT_SUCCESS;

    for (int i = 1; i < argc; ++i) {
        char *end = NULL;
        long value;

        errno = 0;
        value = strtol(argv[i], &end, 10);

        if (errno == ERANGE || end == argv[i] || *end != '\0') {
            fprintf(stderr, "Invalid integer: %s\n", argv[i]);
            free_list(head);
            return EXIT_FAILURE;
        }

        if (!append_value(&head, &tail, value)) {
            fputs("Failed to allocate input list\n", stderr);
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    encoded = modified_run_length_encode(head);
    if (head != NULL && encoded == NULL) {
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