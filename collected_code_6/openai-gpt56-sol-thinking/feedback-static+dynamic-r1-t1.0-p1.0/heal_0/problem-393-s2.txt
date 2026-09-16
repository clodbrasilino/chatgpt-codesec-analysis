#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static bool get_list_length(const Node *head, size_t *length)
{
    const Node *slow = head;
    const Node *fast = head;
    const Node *current;
    size_t count = 0;

    if (length == NULL) {
        return false;
    }

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return false;
        }
    }

    current = head;

    while (current != NULL) {
        if (count == SIZE_MAX) {
            return false;
        }

        ++count;
        current = current->next;
    }

    *length = count;
    return true;
}

static bool find_longest_list(
    const Node *const lists[],
    size_t list_count,
    const Node **longest_list,
    size_t *longest_length,
    size_t *longest_index)
{
    const Node *best_list;
    size_t best_length;
    size_t current_length;
    size_t best_index = 0;
    size_t i;

    if (lists == NULL || list_count == 0 || longest_list == NULL ||
        longest_length == NULL || longest_index == NULL) {
        return false;
    }

    if (!get_list_length(lists[0], &best_length)) {
        return false;
    }

    best_list = lists[0];

    for (i = 1; i < list_count; ++i) {
        if (!get_list_length(lists[i], &current_length)) {
            return false;
        }

        if (current_length > best_length) {
            best_list = lists[i];
            best_length = current_length;
            best_index = i;
        }
    }

    *longest_list = best_list;
    *longest_length = best_length;
    *longest_index = best_index;

    return true;
}

static bool print_list(const Node *head)
{
    const Node *current = head;

    while (current != NULL) {
        if (printf("%d%s", current->value,
                   current->next != NULL ? " " : "\n") < 0) {
            return false;
        }

        current = current->next;
    }

    if (head == NULL && putchar('\n') == EOF) {
        return false;
    }

    return true;
}

int main(void)
{
    Node first[] = {
        {1, NULL},
        {2, NULL},
        {3, NULL}
    };
    Node second[] = {
        {10, NULL},
        {20, NULL},
        {30, NULL},
        {40, NULL},
        {50, NULL}
    };
    Node third[] = {
        {100, NULL},
        {200, NULL},
        {300, NULL},
        {400, NULL}
    };
    const Node *lists[3];
    const Node *longest;
    size_t longest_length;
    size_t longest_index;

    first[0].next = &first[1];
    first[1].next = &first[2];

    second[0].next = &second[1];
    second[1].next = &second[2];
    second[2].next = &second[3];
    second[3].next = &second[4];

    third[0].next = &third[1];
    third[1].next = &third[2];
    third[2].next = &third[3];

    lists[0] = first;
    lists[1] = second;
    lists[2] = third;

    if (!find_longest_list(
            lists,
            sizeof(lists) / sizeof(lists[0]),
            &longest,
            &longest_length,
            &longest_index)) {
        if (fputs("Unable to find the longest list.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Longest list index: %zu\n", longest_index) < 0 ||
        printf("Longest list length: %zu\n", longest_length) < 0 ||
        !print_list(longest)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}