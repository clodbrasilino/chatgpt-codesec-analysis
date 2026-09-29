#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *elements;
    size_t count;
} Tuple;

int tuple_intersection(const Tuple *tuples, size_t tuple_count,
                       int **result, size_t *result_count)
{
    int *intersection = NULL;
    size_t intersection_count = 0;

    if (result == NULL || result_count == NULL) {
        return EINVAL;
    }

    *result = NULL;
    *result_count = 0;

    if (tuple_count == 0) {
        return 0;
    }

    if (tuples == NULL) {
        return EINVAL;
    }

    for (size_t i = 0; i < tuple_count; ++i) {
        if (tuples[i].count > 0 && tuples[i].elements == NULL) {
            return EINVAL;
        }
    }

    if (tuples[0].count == 0) {
        return 0;
    }

    if (tuples[0].count > SIZE_MAX / sizeof(*intersection)) {
        return ENOMEM;
    }

    intersection = malloc(tuples[0].count * sizeof(*intersection));
    if (intersection == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0; i < tuples[0].count; ++i) {
        int candidate = tuples[0].elements[i];
        int present_in_all = 1;
        int already_added = 0;

        for (size_t j = 0; j < intersection_count; ++j) {
            if (intersection[j] == candidate) {
                already_added = 1;
                break;
            }
        }

        if (already_added) {
            continue;
        }

        for (size_t tuple_index = 1; tuple_index < tuple_count; ++tuple_index) {
            int found = 0;

            for (size_t element_index = 0;
                 element_index < tuples[tuple_index].count;
                 ++element_index) {
                if (tuples[tuple_index].elements[element_index] == candidate) {
                    found = 1;
                    break;
                }
            }

            if (!found) {
                present_in_all = 0;
                break;
            }
        }

        if (present_in_all) {
            intersection[intersection_count++] = candidate;
        }
    }

    if (intersection_count == 0) {
        free(intersection);
        intersection = NULL;
    } else {
        int *resized = realloc(intersection,
                               intersection_count * sizeof(*intersection));
        if (resized != NULL) {
            intersection = resized;
        }
    }

    *result = intersection;
    *result_count = intersection_count;
    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5};
    const int second[] = {5, 3, 7, 1};
    const int third[] = {8, 1, 3, 9};

    const Tuple tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    int *intersection = NULL;
    size_t intersection_count = 0;
    int status = tuple_intersection(
        tuples,
        sizeof(tuples) / sizeof(tuples[0]),
        &intersection,
        &intersection_count
    );

    if (status != 0) {
        if (fprintf(stderr, "Failed to find intersection: %d\n", status) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (fputc('(', stdout) == EOF) {
        free(intersection);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < intersection_count; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            free(intersection);
            return EXIT_FAILURE;
        }

        if (printf("%d", intersection[i]) < 0) {
            free(intersection);
            return EXIT_FAILURE;
        }
    }

    if (fputs(")\n", stdout) == EOF) {
        free(intersection);
        return EXIT_FAILURE;
    }

    free(intersection);
    return EXIT_SUCCESS;
}