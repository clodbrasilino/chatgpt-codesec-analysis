#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

typedef struct {
    int element;
    int *partners;
    size_t partner_count;
} Assignment;

static void free_assignments(Assignment *assignments, size_t count)
{
    if (assignments == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(assignments[i].partners);
    }

    free(assignments);
}

static int find_element(const int *elements, size_t count, int value, size_t *index)
{
    if (elements == NULL || index == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (elements[i] == value) {
            *index = i;
            return 1;
        }
    }

    return 0;
}

static int build_assignments(const Pair *pairs, size_t pair_count,
                             Assignment **result, size_t *result_count)
{
    int *elements = NULL;
    size_t *counts = NULL;
    Assignment *assignments = NULL;
    size_t element_count = 0;
    size_t capacity;

    if (pairs == NULL || result == NULL || result_count == NULL) {
        return 0;
    }

    *result = NULL;
    *result_count = 0;

    if (pair_count > SIZE_MAX / 2U) {
        return 0;
    }

    capacity = pair_count * 2U;

    if (capacity > SIZE_MAX / sizeof(*elements)) {
        return 0;
    }

    elements = malloc(capacity * sizeof(*elements));
    if (elements == NULL && capacity != 0U) {
        return 0;
    }

    for (size_t i = 0; i < pair_count; ++i) {
        size_t index;

        if (!find_element(elements, element_count, pairs[i].first, &index)) {
            elements[element_count++] = pairs[i].first;
        }

        if (!find_element(elements, element_count, pairs[i].second, &index)) {
            elements[element_count++] = pairs[i].second;
        }
    }

    if (element_count > SIZE_MAX / sizeof(*assignments)) {
        free(elements);
        return 0;
    }

    assignments = calloc(element_count, sizeof(*assignments));
    counts = calloc(element_count, sizeof(*counts));

    if ((assignments == NULL || counts == NULL) && element_count != 0U) {
        free(counts);
        free(assignments);
        free(elements);
        return 0;
    }

    for (size_t i = 0; i < element_count; ++i) {
        assignments[i].element = elements[i];
    }

    for (size_t i = 0; i < pair_count; ++i) {
        size_t first_index;
        size_t second_index;

        if (!find_element(elements, element_count, pairs[i].first, &first_index) ||
            !find_element(elements, element_count, pairs[i].second, &second_index)) {
            free(counts);
            free(elements);
            free_assignments(assignments, element_count);
            return 0;
        }

        ++counts[first_index];
        ++counts[second_index];
    }

    for (size_t i = 0; i < element_count; ++i) {
        if (counts[i] > SIZE_MAX / sizeof(*assignments[i].partners)) {
            free(counts);
            free(elements);
            free_assignments(assignments, element_count);
            return 0;
        }

        assignments[i].partners = malloc(counts[i] * sizeof(*assignments[i].partners));
        if (assignments[i].partners == NULL && counts[i] != 0U) {
            free(counts);
            free(elements);
            free_assignments(assignments, element_count);
            return 0;
        }
    }

    for (size_t i = 0; i < pair_count; ++i) {
        size_t first_index;
        size_t second_index;

        if (!find_element(elements, element_count, pairs[i].first, &first_index) ||
            !find_element(elements, element_count, pairs[i].second, &second_index)) {
            free(counts);
            free(elements);
            free_assignments(assignments, element_count);
            return 0;
        }

        assignments[first_index].partners[assignments[first_index].partner_count++] =
            pairs[i].second;
        assignments[second_index].partners[assignments[second_index].partner_count++] =
            pairs[i].first;
    }

    free(counts);
    free(elements);

    *result = assignments;
    *result_count = element_count;
    return 1;
}

int main(void)
{
    const Pair pairs[] = {
        {1, 2},
        {1, 3},
        {2, 4},
        {3, 4},
        {4, 5}
    };
    Assignment *assignments = NULL;
    size_t assignment_count = 0;
    const size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);

    if (!build_assignments(pairs, pair_count, &assignments, &assignment_count)) {
        fputs("Failed to build assignments.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < assignment_count; ++i) {
        if (printf("%d:", assignments[i].element) < 0) {
            free_assignments(assignments, assignment_count);
            return EXIT_FAILURE;
        }

        for (size_t j = 0; j < assignments[i].partner_count; ++j) {
            if (printf(" %d", assignments[i].partners[j]) < 0) {
                free_assignments(assignments, assignment_count);
                return EXIT_FAILURE;
            }
        }

        if (putchar('\n') == EOF) {
            free_assignments(assignments, assignment_count);
            return EXIT_FAILURE;
        }
    }

    free_assignments(assignments, assignment_count);
    return EXIT_SUCCESS;
}