#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

typedef struct {
    size_t first_index;
    size_t second_index;
    int64_t value;
    int found;
} MaximumMatch;

static MaximumMatch find_maximum_similar_indices(
    const Tuple *first_list,
    size_t first_count,
    const Tuple *second_list,
    size_t second_count)
{
    MaximumMatch result = {0U, 0U, 0, 0};

    if ((first_list == NULL && first_count != 0U) ||
        (second_list == NULL && second_count != 0U)) {
        return result;
    }

    for (size_t i = 0U; i < first_count; ++i) {
        for (size_t j = 0U; j < second_count; ++j) {
            if (first_list[i].first == second_list[j].first) {
                int64_t candidate =
                    first_list[i].second > second_list[j].second
                        ? first_list[i].second
                        : second_list[j].second;

                if (!result.found || candidate > result.value) {
                    result.first_index = i;
                    result.second_index = j;
                    result.value = candidate;
                    result.found = 1;
                }
            }
        }
    }

    return result;
}

static int read_tuples(Tuple **list, size_t *count)
{
    uintmax_t input_count = 0;

    if (list == NULL || count == NULL) {
        return 0;
    }

    *list = NULL;
    *count = 0U;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNuMAX, &input_count) != 1) {
        return 0;
    }

    if (input_count > (uintmax_t)SIZE_MAX ||
        input_count > (uintmax_t)(SIZE_MAX / sizeof(Tuple))) {
        return 0;
    }

    *count = (size_t)input_count;

    if (*count == 0U) {
        return 1;
    }

    *list = malloc(*count * sizeof(**list));
    if (*list == NULL) {
        *count = 0U;
        return 0;
    }

    for (size_t i = 0U; i < *count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64 " %" SCNd64,
                  &(*list)[i].first,
                  &(*list)[i].second) != 2) {
            free(*list);
            *list = NULL;
            *count = 0U;
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    Tuple *first_list = NULL;
    Tuple *second_list = NULL;
    size_t first_count = 0U;
    size_t second_count = 0U;

    if (!read_tuples(&first_list, &first_count)) {
        fputs("Invalid first list\n", stderr);
        return EXIT_FAILURE;
    }

    if (!read_tuples(&second_list, &second_count)) {
        free(first_list);
        fputs("Invalid second list\n", stderr);
        return EXIT_FAILURE;
    }

    MaximumMatch result = find_maximum_similar_indices(
        first_list,
        first_count,
        second_list,
        second_count
    );

    if (result.found) {
        printf("%zu %zu %" PRId64 "\n",
               result.first_index,
               result.second_index,
               result.value);
    } else {
        puts("No match");
    }

    free(second_list);
    free(first_list);

    return EXIT_SUCCESS;
}