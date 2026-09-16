#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *items;
    size_t length;
} IntList;

typedef struct {
    const IntList *list;
    size_t count;
} Frequency;

static int lists_equal(const IntList *a, const IntList *b)
{
    size_t i;

    if (a == NULL || b == NULL || a->length != b->length) {
        return 0;
    }

    if ((a->length > 0U && a->items == NULL) ||
        (b->length > 0U && b->items == NULL)) {
        return 0;
    }

    for (i = 0U; i < a->length; ++i) {
        if (a->items[i] != b->items[i]) {
            return 0;
        }
    }

    return 1;
}

static int frequency_count(const IntList *lists, size_t list_count,
                           Frequency **result, size_t *result_count)
{
    Frequency *frequencies;
    size_t unique_count;
    size_t i;
    size_t j;

    if (result == NULL || result_count == NULL) {
        return 0;
    }

    *result = NULL;
    *result_count = 0U;

    if (list_count == 0U) {
        return 1;
    }

    if (lists == NULL || list_count > SIZE_MAX / sizeof(*frequencies)) {
        return 0;
    }

    for (i = 0U; i < list_count; ++i) {
        if (lists[i].length > 0U && lists[i].items == NULL) {
            return 0;
        }
    }

    frequencies = calloc(list_count, sizeof(*frequencies));
    if (frequencies == NULL) {
        return 0;
    }

    unique_count = 0U;

    for (i = 0U; i < list_count; ++i) {
        for (j = 0U; j < unique_count; ++j) {
            if (lists_equal(&lists[i], frequencies[j].list)) {
                if (frequencies[j].count == SIZE_MAX) {
                    free(frequencies);
                    return 0;
                }
                ++frequencies[j].count;
                break;
            }
        }

        if (j == unique_count) {
            frequencies[unique_count].list = &lists[i];
            frequencies[unique_count].count = 1U;
            ++unique_count;
        }
    }

    *result = frequencies;
    *result_count = unique_count;
    return 1;
}

static int print_frequencies(const Frequency *frequencies, size_t count)
{
    size_t i;
    size_t j;

    if (count > 0U && frequencies == NULL) {
        return 0;
    }

    for (i = 0U; i < count; ++i) {
        if (frequencies[i].list == NULL ||
            (frequencies[i].list->length > 0U &&
             frequencies[i].list->items == NULL)) {
            return 0;
        }

        if (putchar('[') == EOF) {
            return 0;
        }

        for (j = 0U; j < frequencies[i].list->length; ++j) {
            if (printf("%s%d", j == 0U ? "" : ", ",
                       frequencies[i].list->items[j]) < 0) {
                return 0;
            }
        }

        if (printf("]: %zu\n", frequencies[i].count) < 0) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    int values0[] = {1, 2};
    int values1[] = {3, 4, 5};
    int values2[] = {1, 2};
    int values3[] = {3, 4, 5};
    int values4[] = {7};
    IntList lists[] = {
        {values0, sizeof(values0) / sizeof(values0[0])},
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])},
        {values4, sizeof(values4) / sizeof(values4[0])},
        {NULL, 0U}
    };
    Frequency *frequencies;
    size_t frequency_count_value;
    int status;

    frequencies = NULL;
    frequency_count_value = 0U;

    if (!frequency_count(lists, sizeof(lists) / sizeof(lists[0]),
                         &frequencies, &frequency_count_value)) {
        fputs("Failed to calculate frequencies.\n", stderr);
        return EXIT_FAILURE;
    }

    status = print_frequencies(frequencies, frequency_count_value);
    free(frequencies);

    if (!status) {
        fputs("Failed to print frequencies.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}