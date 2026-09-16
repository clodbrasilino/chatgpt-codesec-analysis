#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t count;
} PointSet;

static int choose_unique_points(int first_start,
                                int first_end,
                                int second_start,
                                int second_end,
                                PointSet *first,
                                PointSet *second)
{
    size_t first_count = 0;
    size_t second_count = 0;
    int value;

    if (first == NULL || second == NULL ||
        first_start > first_end || second_start > second_end) {
        return -1;
    }

    first->values = NULL;
    first->count = 0;
    second->values = NULL;
    second->count = 0;

    for (value = first_start;; ++value) {
        if (value < second_start || value > second_end) {
            ++first_count;
        }
        if (value == first_end) {
            break;
        }
    }

    for (value = second_start;; ++value) {
        if (value < first_start || value > first_end) {
            ++second_count;
        }
        if (value == second_end) {
            break;
        }
    }

    if (first_count > 0) {
        if (first_count > SIZE_MAX / sizeof(*first->values)) {
            return -1;
        }
        first->values = malloc(first_count * sizeof(*first->values));
        if (first->values == NULL) {
            return -1;
        }
    }

    if (second_count > 0) {
        if (second_count > SIZE_MAX / sizeof(*second->values)) {
            free(first->values);
            first->values = NULL;
            return -1;
        }
        second->values = malloc(second_count * sizeof(*second->values));
        if (second->values == NULL) {
            free(first->values);
            first->values = NULL;
            return -1;
        }
    }

    first->count = first_count;
    second->count = second_count;
    first_count = 0;
    second_count = 0;

    for (value = first_start;; ++value) {
        if (value < second_start || value > second_end) {
            first->values[first_count++] = value;
        }
        if (value == first_end) {
            break;
        }
    }

    for (value = second_start;; ++value) {
        if (value < first_start || value > first_end) {
            second->values[second_count++] = value;
        }
        if (value == second_end) {
            break;
        }
    }

    return 0;
}

static void free_point_set(PointSet *set)
{
    if (set != NULL) {
        free(set->values);
        set->values = NULL;
        set->count = 0;
    }
}

static void print_point_set(const char *name, const PointSet *set)
{
    size_t index;

    printf("%s:", name);
    for (index = 0; index < set->count; ++index) {
        printf(" %d", set->values[index]);
    }
    putchar('\n');
}

int main(void)
{
    int first_start;
    int first_end;
    int second_start;
    int second_end;
    PointSet first = {NULL, 0};
    PointSet second = {NULL, 0};

    if (scanf("%d %d %d %d",
              &first_start,
              &first_end,
              &second_start,
              &second_end) != 4) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (choose_unique_points(first_start,
                             first_end,
                             second_start,
                             second_end,
                             &first,
                             &second) != 0) {
        fputs("Unable to choose points\n", stderr);
        return EXIT_FAILURE;
    }

    print_point_set("First range", &first);
    print_point_set("Second range", &second);

    free_point_set(&first);
    free_point_set(&second);

    return EXIT_SUCCESS;
}