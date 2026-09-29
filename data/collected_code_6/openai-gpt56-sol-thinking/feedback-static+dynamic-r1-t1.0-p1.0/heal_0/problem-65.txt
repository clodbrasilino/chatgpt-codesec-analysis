#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int64_t value;
    struct Node *next;
} Node;

bool recursive_list_sum(const Node *node, int64_t *result)
{
    int64_t remaining_sum;

    if (result == NULL) {
        return false;
    }

    if (node == NULL) {
        *result = 0;
        return true;
    }

    if (!recursive_list_sum(node->next, &remaining_sum)) {
        return false;
    }

    if ((node->value > 0 && remaining_sum > INT64_MAX - node->value) ||
        (node->value < 0 && remaining_sum < INT64_MIN - node->value)) {
        return false;
    }

    *result = node->value + remaining_sum;
    return true;
}

int main(void)
{
    Node fifth = {5, NULL};
    Node fourth = {4, &fifth};
    Node third = {3, &fourth};
    Node second = {2, &third};
    Node first = {1, &second};
    int64_t sum;

    if (!recursive_list_sum(&first, &sum)) {
        fputs("Unable to calculate the list sum.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}