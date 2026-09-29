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

static EncodedNode *modified_run_length_encode(const ListNode *head)
{
    EncodedNode *result = NULL;
    EncodedNode *tail = NULL;

    while (head != NULL) {
        const long value = head->value;
        size_t count = 0;

        do {
            if (count == SIZE_MAX) {
                free_encoded_list(result);
                return NULL;
            }

            ++count;
            head = head->next;
        } while (head != NULL && head->value == value);

        EncodedNode *node = malloc(sizeof *node);
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
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    ListNode *head = NULL;
    ListNode *tail = NULL;
    int exit_status = EXIT_SUCCESS;

    for (int i = 1; i < argc; ++i) {
        const char *const argument = argv[i];
        char *end = NULL;

        errno = 0;
        const long value = strtol(argument, &end, 10);

        if (errno == ERANGE || end == argument || *end != '\0') {
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

    EncodedNode *encoded = modified_run_length_encode(head);

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