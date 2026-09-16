#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FIND_SUCCESS,
    FIND_INVALID_ARGUMENT,
    FIND_ALLOCATION_FAILURE
} FindStatus;

static int compare_integers(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static FindStatus find_most_frequent(const int *items, size_t count,
                                     int *result, size_t *frequency)
{
    int *copy;
    int current_item;
    int most_frequent_item;
    size_t current_frequency = 1;
    size_t maximum_frequency = 1;

    if (items == NULL || result == NULL || frequency == NULL || count == 0) {
        return FIND_INVALID_ARGUMENT;
    }

    if (count > SIZE_MAX / sizeof(*copy)) {
        return FIND_ALLOCATION_FAILURE;
    }

    copy = malloc(count * sizeof(*copy));
    if (copy == NULL) {
        return FIND_ALLOCATION_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        copy[i] = items[i];
    }

    qsort(copy, count, sizeof(*copy), compare_integers);

    current_item = copy[0];
    most_frequent_item = copy[0];

    for (size_t i = 1; i < count; ++i) {
        if (copy[i] == current_item) {
            ++current_frequency;
        } else {
            if (current_frequency > maximum_frequency) {
                maximum_frequency = current_frequency;
                most_frequent_item = current_item;
            }

            current_item = copy[i];
            current_frequency = 1;
        }
    }

    if (current_frequency > maximum_frequency) {
        maximum_frequency = current_frequency;
        most_frequent_item = current_item;
    }

    free(copy);

    *result = most_frequent_item;
    *frequency = maximum_frequency;

    return FIND_SUCCESS;
}

int main(void)
{
    const int items[] = {4, 2, 7, 4, 9, 2, 4, 7, 4, 2};
    const size_t count = sizeof(items) / sizeof(items[0]);
    int most_frequent_item;
    size_t frequency;
    FindStatus status;

    status = find_most_frequent(items, count, &most_frequent_item, &frequency);
    if (status != FIND_SUCCESS) {
        if (fprintf(stderr, "Unable to find the most frequent item.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Item: %d\nFrequency: %zu\n",
               most_frequent_item, frequency) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}