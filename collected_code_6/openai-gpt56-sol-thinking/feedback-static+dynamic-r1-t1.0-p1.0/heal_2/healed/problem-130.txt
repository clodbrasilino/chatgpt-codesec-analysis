#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FIND_SUCCESS = 0,
    FIND_INVALID_ARGUMENT,
    FIND_MEMORY_ERROR
} FindResult;

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static FindResult find_most_frequent(const int *items,
                                     size_t count,
                                     int *result_item,
                                     size_t *result_frequency)
{
    int *sorted_items;
    int best_item;
    size_t best_frequency;
    size_t current_frequency;
    size_t i;

    if (items == NULL || count == 0U ||
        result_item == NULL || result_frequency == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    if (count > SIZE_MAX / sizeof(*sorted_items)) {
        return FIND_MEMORY_ERROR;
    }

    sorted_items = malloc(count * sizeof(*sorted_items));
    if (sorted_items == NULL) {
        return FIND_MEMORY_ERROR;
    }

    for (i = 0U; i < count; ++i) {
        sorted_items[i] = items[i];
    }

    qsort(sorted_items, count, sizeof(*sorted_items), compare_ints);

    best_item = sorted_items[0];
    best_frequency = 1U;
    current_frequency = 1U;

    for (i = 1U; i < count; ++i) {
        if (sorted_items[i] == sorted_items[i - 1U]) {
            ++current_frequency;
        } else {
            if (current_frequency > best_frequency) {
                best_frequency = current_frequency;
                best_item = sorted_items[i - 1U];
            }

            current_frequency = 1U;
        }
    }

    if (current_frequency > best_frequency) {
        best_frequency = current_frequency;
        best_item = sorted_items[count - 1U];
    }

    free(sorted_items);

    *result_item = best_item;
    *result_frequency = best_frequency;

    return FIND_SUCCESS;
}

static int parse_integer(const char *text, int *result)
{
    char *end;
    long value;

    if (text == NULL || result == NULL) {
        return 0;
    }

    errno = 0;
    end = NULL;
    value = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || end == NULL || *end != '\0' ||
        value < INT_MIN || value > INT_MAX) {
        return 0;
    }

    *result = (int)value;
    return 1;
}

int main(int argc, char * const argv[])
{
    int *items;
    int most_frequent_item;
    size_t count;
    size_t frequency;
    size_t i;
    FindResult result;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s integer [integer ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (count > SIZE_MAX / sizeof(*items)) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    items = malloc(count * sizeof(*items));
    if (items == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (!parse_integer(argv[i + 1U], &items[i])) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 1U]);
            free(items);
            return EXIT_FAILURE;
        }
    }

    result = find_most_frequent(items, count,
                                &most_frequent_item, &frequency);

    free(items);

    if (result != FIND_SUCCESS) {
        fputs("Unable to determine the most frequent item.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Item: %d\nFrequency: %zu\n",
           most_frequent_item, frequency);

    return EXIT_SUCCESS;
}