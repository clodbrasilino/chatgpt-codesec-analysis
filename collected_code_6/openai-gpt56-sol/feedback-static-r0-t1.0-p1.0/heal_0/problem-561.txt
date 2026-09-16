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

static int find_element(const Assignment *assignments, size_t count, int element,
                        size_t *index)
{
    for (size_t i = 0; i < count; ++i) {
        if (assignments[i].element == element) {
            *index = i;
            return 1;
        }
    }

    return 0;
}

static int add_partner(Assignment *assignment, int partner)
{
    for (size_t i = 0; i < assignment->partner_count; ++i) {
        if (assignment->partners[i] == partner) {
            return 1;
        }
    }

    if (assignment->partner_count == SIZE_MAX / sizeof(*assignment->partners)) {
        return 0;
    }

    size_t new_count = assignment->partner_count + 1;
    int *new_partners = realloc(
        assignment->partners,
        new_count * sizeof(*assignment->partners)
    );

    if (new_partners == NULL) {
        return 0;
    }

    assignment->partners = new_partners;
    assignment->partners[assignment->partner_count] = partner;
    assignment->partner_count = new_count;
    return 1;
}

static int add_assignment(Assignment **assignments, size_t *count, int element,
                          size_t *index)
{
    if (*count == SIZE_MAX / sizeof(**assignments)) {
        return 0;
    }

    size_t new_count = *count + 1;
    Assignment *new_assignments = realloc(
        *assignments,
        new_count * sizeof(**assignments)
    );

    if (new_assignments == NULL) {
        return 0;
    }

    *assignments = new_assignments;
    *index = *count;
    (*assignments)[*index].element = element;
    (*assignments)[*index].partners = NULL;
    (*assignments)[*index].partner_count = 0;
    *count = new_count;
    return 1;
}

static int assign_pair_elements(const Pair *pairs, size_t pair_count,
                                Assignment **result, size_t *result_count)
{
    if (result == NULL || result_count == NULL ||
        (pairs == NULL && pair_count != 0)) {
        return 0;
    }

    *result = NULL;
    *result_count = 0;

    for (size_t i = 0; i < pair_count; ++i) {
        size_t first_index;
        size_t second_index;

        if (!find_element(*result, *result_count, pairs[i].first, &first_index) &&
            !add_assignment(result, result_count, pairs[i].first, &first_index)) {
            free_assignments(*result, *result_count);
            *result = NULL;
            *result_count = 0;
            return 0;
        }

        if (!find_element(*result, *result_count, pairs[i].second, &second_index) &&
            !add_assignment(result, result_count, pairs[i].second, &second_index)) {
            free_assignments(*result, *result_count);
            *result = NULL;
            *result_count = 0;
            return 0;
        }

        if (!add_partner(&(*result)[first_index], pairs[i].second) ||
            !add_partner(&(*result)[second_index], pairs[i].first)) {
            free_assignments(*result, *result_count);
            *result = NULL;
            *result_count = 0;
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    const Pair pairs[] = {
        {1, 2},
        {3, 4},
        {1, 5},
        {2, 3},
        {4, 5}
    };
    const size_t pair_count = sizeof(pairs) / sizeof(pairs[0]);
    Assignment *assignments = NULL;
    size_t assignment_count = 0;

    if (!assign_pair_elements(pairs, pair_count, &assignments,
                              &assignment_count)) {
        fputs("Failed to assign pair elements.\n", stderr);
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