#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int64_t value;
    struct ListNode *next;
} ListNode;

typedef enum {
    LIST_OK,
    LIST_INVALID_ARGUMENT,
    LIST_LENGTH_MISMATCH,
    LIST_ARITHMETIC_OVERFLOW,
    LIST_ALLOCATION_FAILURE
} ListStatus;

static void free_list(ListNode *head)
{
    while (head != NULL) {
        ListNode *next = head->next;
        free(head);
        head = next;
    }
}

static ListStatus list_from_array(const int64_t *values, size_t count,
                                  ListNode **result)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;

    if (result == NULL || (count != 0U && values == NULL)) {
        return LIST_INVALID_ARGUMENT;
    }

    *result = NULL;

    for (size_t i = 0U; i < count; ++i) {
        ListNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(head);
            return LIST_ALLOCATION_FAILURE;
        }

        node->value = values[i];
        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    *result = head;
    return LIST_OK;
}

static bool subtract_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return false;
    }

    if ((right > 0 && left < INT64_MIN + right) ||
        (right < 0 && left > INT64_MAX + right)) {
        return false;
    }

    *result = left - right;
    return true;
}

static ListStatus subtract_lists(const ListNode *left, const ListNode *right,
                                 ListNode **result)
{
    ListNode *head = NULL;
    ListNode *tail = NULL;

    if (result == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    *result = NULL;

    while (left != NULL && right != NULL) {
        int64_t value;
        ListNode *node;

        if (!subtract_int64(left->value, right->value, &value)) {
            free_list(head);
            return LIST_ARITHMETIC_OVERFLOW;
        }

        node = malloc(sizeof(*node));
        if (node == NULL) {
            free_list(head);
            return LIST_ALLOCATION_FAILURE;
        }

        node->value = value;
        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
        left = left->next;
        right = right->next;
    }

    if (left != NULL || right != NULL) {
        free_list(head);
        return LIST_LENGTH_MISMATCH;
    }

    *result = head;
    return LIST_OK;
}

static int print_int64(int64_t value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char digits[sizeof(uint64_t) * CHAR_BIT];
    uint64_t magnitude;
    size_t length = 0U;

    if (value < 0) {
        if (fputc('-', stdout) == EOF) {
            return -1;
        }

        magnitude = (uint64_t)(-(value + 1)) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)value;
    }

    do {
        digits[length++] = (char)('0' + (magnitude % UINT64_C(10)));
        magnitude /= UINT64_C(10);
    } while (magnitude != 0U);

    while (length != 0U) {
        if (fputc((unsigned char)digits[--length], stdout) == EOF) {
            return -1;
        }
    }

    return 0;
}

static int print_list(const ListNode *head)
{
    bool first = true;

    while (head != NULL) {
        if (!first && fputc(' ', stdout) == EOF) {
            return -1;
        }

        if (print_int64(head->value) != 0) {
            return -1;
        }

        first = false;
        head = head->next;
    }

    return fputc('\n', stdout) == EOF ? -1 : 0;
}

static const char *status_message(ListStatus status)
{
    switch (status) {
        case LIST_OK:
            return "success";
        case LIST_INVALID_ARGUMENT:
            return "invalid argument";
        case LIST_LENGTH_MISMATCH:
            return "list length mismatch";
        case LIST_ARITHMETIC_OVERFLOW:
            return "arithmetic overflow";
        case LIST_ALLOCATION_FAILURE:
            return "memory allocation failure";
        default:
            return "unknown error";
    }
}

static void report_error(const char *message)
{
    if (message != NULL) {
        (void)fputs(message, stderr);
        (void)fputc('\n', stderr);
    }
}

int main(void)
{
    const int64_t left_values[] = {10, 20, 30, 40};
    const int64_t right_values[] = {2, 7, 12, 15};
    const size_t left_count = sizeof(left_values) / sizeof(left_values[0]);
    const size_t right_count = sizeof(right_values) / sizeof(right_values[0]);
    ListNode *left = NULL;
    ListNode *right = NULL;
    ListNode *difference = NULL;
    ListStatus status;
    int exit_status = EXIT_FAILURE;

    status = list_from_array(left_values, left_count, &left);
    if (status != LIST_OK) {
        report_error(status_message(status));
        goto cleanup;
    }

    status = list_from_array(right_values, right_count, &right);
    if (status != LIST_OK) {
        report_error(status_message(status));
        goto cleanup;
    }

    status = subtract_lists(left, right, &difference);
    if (status != LIST_OK) {
        report_error(status_message(status));
        goto cleanup;
    }

    if (print_list(difference) != 0) {
        report_error("output failure");
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free_list(difference);
    free_list(right);
    free_list(left);

    return exit_status;
}