#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int key;
    int *values;
    size_t count;
    size_t capacity;
} Group;

typedef struct {
    Group *groups;
    size_t count;
    size_t capacity;
} GroupList;

static int calculate_capacity(size_t current, size_t required,
                              size_t element_size, size_t *new_capacity)
{
    size_t capacity = current == 0U ? 4U : current;

    if (new_capacity == NULL || element_size == 0U ||
        required > SIZE_MAX / element_size) {
        return -1;
    }

    while (capacity < required) {
        if (capacity > SIZE_MAX / 2U) {
            capacity = required;
            break;
        }
        capacity *= 2U;
    }

    if (capacity > SIZE_MAX / element_size) {
        return -1;
    }

    *new_capacity = capacity;
    return 0;
}

void free_group_list(GroupList *group_list)
{
    size_t index;

    if (group_list == NULL) {
        return;
    }

    for (index = 0U; index < group_list->count; ++index) {
        free(group_list->groups[index].values);
    }

    free(group_list->groups);
    group_list->groups = NULL;
    group_list->count = 0U;
    group_list->capacity = 0U;
}

int group_tuples(const Tuple *tuples, size_t tuple_count, GroupList *result)
{
    GroupList temporary = {NULL, 0U, 0U};
    size_t tuple_index;

    if (result == NULL || (tuples == NULL && tuple_count != 0U) ||
        result->groups != NULL || result->count != 0U ||
        result->capacity != 0U) {
        return -1;
    }

    for (tuple_index = 0U; tuple_index < tuple_count; ++tuple_index) {
        size_t group_index;

        for (group_index = 0U; group_index < temporary.count; ++group_index) {
            if (temporary.groups[group_index].key ==
                tuples[tuple_index].second) {
                break;
            }
        }

        if (group_index == temporary.count) {
            Group *resized_groups;
            size_t new_capacity;

            if (temporary.count == SIZE_MAX ||
                calculate_capacity(temporary.capacity,
                                   temporary.count + 1U,
                                   sizeof(*temporary.groups),
                                   &new_capacity) != 0) {
                free_group_list(&temporary);
                return -1;
            }

            if (new_capacity != temporary.capacity) {
                resized_groups = realloc(
                    temporary.groups,
                    new_capacity * sizeof(*temporary.groups));

                if (resized_groups == NULL) {
                    free_group_list(&temporary);
                    return -1;
                }

                temporary.groups = resized_groups;
                temporary.capacity = new_capacity;
            }

            temporary.groups[group_index].key = tuples[tuple_index].second;
            temporary.groups[group_index].values = NULL;
            temporary.groups[group_index].count = 0U;
            temporary.groups[group_index].capacity = 0U;
            ++temporary.count;
        }

        {
            Group *group = &temporary.groups[group_index];

            if (group->count == SIZE_MAX) {
                free_group_list(&temporary);
                return -1;
            }

            if (group->count == group->capacity) {
                int *resized_values;
                size_t new_capacity;

                if (calculate_capacity(group->capacity,
                                       group->count + 1U,
                                       sizeof(*group->values),
                                       &new_capacity) != 0) {
                    free_group_list(&temporary);
                    return -1;
                }

                resized_values = realloc(
                    group->values,
                    new_capacity * sizeof(*group->values));

                if (resized_values == NULL) {
                    free_group_list(&temporary);
                    return -1;
                }

                group->values = resized_values;
                group->capacity = new_capacity;
            }

            group->values[group->count] = tuples[tuple_index].first;
            ++group->count;
        }
    }

    *result = temporary;
    return 0;
}

int print_group_list(const GroupList *group_list)
{
    size_t group_index;

    if (group_list == NULL) {
        return -1;
    }

    for (group_index = 0U; group_index < group_list->count; ++group_index) {
        size_t value_index;
        const Group *group = &group_list->groups[group_index];

        if (printf("%d: [", group->key) < 0) {
            return -1;
        }

        for (value_index = 0U; value_index < group->count; ++value_index) {
            if (printf("%s%d",
                       value_index == 0U ? "" : ", ",
                       group->values[value_index]) < 0) {
                return -1;
            }
        }

        if (printf("]\n") < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const Tuple tuples[] = {
        {1, 2},
        {2, 2},
        {3, 1},
        {4, 1},
        {5, 3},
        {6, 2}
    };
    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    GroupList grouped = {NULL, 0U, 0U};
    int status = EXIT_SUCCESS;

    if (group_tuples(tuples, tuple_count, &grouped) != 0) {
        return EXIT_FAILURE;
    }

    if (print_group_list(&grouped) != 0) {
        status = EXIT_FAILURE;
    }

    free_group_list(&grouped);
    return status;
}