#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Tuple {
    long long first;
    long long second;
    struct Tuple *next;
} Tuple;

static int checked_add(long long left, long long right, long long *result)
{
    if (result == NULL) {
        return -1;
    }

    if ((right > 0 && left > LLONG_MAX - right) ||
        (right < 0 && left < LLONG_MIN - right)) {
        return -1;
    }

    *result = left + right;
    return 0;
}

static int sum_alternate_chains(const Tuple *head, long long *first_sum,
                                long long *second_sum)
{
    size_t index = 0;
    long long even_sum = 0;
    long long odd_sum = 0;

    if (first_sum == NULL || second_sum == NULL) {
        return -1;
    }

    while (head != NULL) {
        long long value;

        if (checked_add(head->first, head->second, &value) != 0) {
            return -1;
        }

        if ((index % 2U) == 0U) {
            if (checked_add(even_sum, value, &even_sum) != 0) {
                return -1;
            }
        } else {
            if (checked_add(odd_sum, value, &odd_sum) != 0) {
                return -1;
            }
        }

        head = head->next;
        ++index;
    }

    *first_sum = even_sum;
    *second_sum = odd_sum;
    return 0;
}

static void free_chain(Tuple *head)
{
    while (head != NULL) {
        Tuple *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    Tuple *head = NULL;
    Tuple *tail = NULL;
    size_t count;
    long long even_sum;
    long long odd_sum;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(Tuple)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        Tuple *node = malloc(sizeof(*node));

        if (node == NULL) {
            fputs("Memory allocation failed\n", stderr);
            free_chain(head);
            return EXIT_FAILURE;
        }

        if (scanf("%lld %lld", &node->first, &node->second) != 2) {
            fputs("Invalid tuple input\n", stderr);
            free(node);
            free_chain(head);
            return EXIT_FAILURE;
        }

        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    if (sum_alternate_chains(head, &even_sum, &odd_sum) != 0) {
        fputs("Arithmetic overflow or invalid argument\n", stderr);
        free_chain(head);
        return EXIT_FAILURE;
    }

    printf("%lld %lld\n", even_sum, odd_sum);
    free_chain(head);
    return EXIT_SUCCESS;
}