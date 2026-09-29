#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

static bool tuples_equal(const Tuple *a, const Tuple *b)
{
    return (a->first == b->first) && (a->second == b->second);
}

static bool tuple_in_list(const Tuple *t, const Tuple *list, size_t count)
{
    size_t i;

    for (i = 0; i < count; i++) {
        if (tuples_equal(t, &list[i])) {
            return true;
        }
    }
    return false;
}

static Tuple *remove_matching_tuples(const Tuple *list1, size_t count1,
                                     const Tuple *list2, size_t count2,
                                     size_t *result_count)
{
    Tuple *result;
    size_t i;
    size_t n = 0;

    if (result_count == NULL) {
        return NULL;
    }
    *result_count = 0;

    if (list1 == NULL || count1 == 0) {
        return NULL;
    }

    result = malloc(count1 * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count1; i++) {
        if (!tuple_in_list(&list1[i], list2, (list2 != NULL) ? count2 : 0)) {
            result[n] = list1[i];
            n++;
        }
    }

    *result_count = n;
    return result;
}

static void print_tuples(const Tuple *list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        if (printf("(%d, %d)\n", list[i].first, list[i].second) < 0) {
            return;
        }
    }
}

int main(void)
{
    Tuple list1[] = { {1, 2}, {3, 4}, {5, 6}, {7, 8} };
    Tuple list2[] = { {3, 4}, {7, 8}, {9, 10} };
    size_t count1 = sizeof(list1) / sizeof(list1[0]);
    size_t count2 = sizeof(list2) / sizeof(list2[0]);
    size_t result_count = 0;
    Tuple *result;

    result = remove_matching_tuples(list1, count1, list2, count2, &result_count);
    if (result == NULL) {
        if (fprintf(stderr, "Memory allocation failed or empty result\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Tuples after removing matches:\n") < 0) {
        free(result);
        return EXIT_FAILURE;
    }
    print_tuples(result, result_count);

    free(result);
    return EXIT_SUCCESS;
}