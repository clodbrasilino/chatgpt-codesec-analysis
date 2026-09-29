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
    for (i = 0U; i < count; i++) {
        if (tuples_equal(t, &list[i])) {
            return true;
        }
    }
    return false;
}

static int remove_matching_tuples(const Tuple *list1, size_t count1,
                                  const Tuple *list2, size_t count2,
                                  Tuple **result, size_t *result_count)
{
    Tuple *out;
    size_t i;
    size_t n;

    if ((result == NULL) || (result_count == NULL)) {
        return -1;
    }
    if ((count1 > 0U) && (list1 == NULL)) {
        return -1;
    }
    if ((count2 > 0U) && (list2 == NULL)) {
        return -1;
    }

    *result = NULL;
    *result_count = 0U;

    if (count1 == 0U) {
        return 0;
    }

    out = (Tuple *)malloc(count1 * sizeof(Tuple));
    if (out == NULL) {
        return -1;
    }

    n = 0U;
    for (i = 0U; i < count1; i++) {
        if (!tuple_in_list(&list1[i], list2, count2)) {
            out[n] = list1[i];
            n++;
        }
    }

    if (n == 0U) {
        free(out);
        out = NULL;
    }

    *result = out;
    *result_count = n;
    return 0;
}

static void print_tuples(const Tuple *list, size_t count)
{
    size_t i;
    if (list == NULL) {
        (void)printf("(empty)\n");
        return;
    }
    for (i = 0U; i < count; i++) {
        (void)printf("(%d, %d)\n", list[i].first, list[i].second);
    }
}

int main(void)
{
    Tuple list1[] = { {1, 2}, {3, 4}, {5, 6}, {7, 8} };
    Tuple list2[] = { {3, 4}, {7, 8}, {9, 10} };
    Tuple *result = NULL;
    size_t result_count = 0U;
    size_t count1 = sizeof(list1) / sizeof(list1[0]);
    size_t count2 = sizeof(list2) / sizeof(list2[0]);

    if (remove_matching_tuples(list1, count1, list2, count2,
                               &result, &result_count) != 0) {
        (void)fprintf(stderr, "Error: failed to remove matching tuples\n");
        return EXIT_FAILURE;
    }

    (void)printf("Remaining tuples after removal:\n");
    print_tuples(result, result_count);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}