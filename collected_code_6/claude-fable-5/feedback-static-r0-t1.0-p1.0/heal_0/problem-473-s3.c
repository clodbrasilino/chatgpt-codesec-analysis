#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static Tuple normalize(Tuple t)
{
    Tuple r;
    if (t.first <= t.second) {
        r.first = t.first;
        r.second = t.second;
    } else {
        r.first = t.second;
        r.second = t.first;
    }
    return r;
}

static int tuples_equal(Tuple a, Tuple b)
{
    Tuple na = normalize(a);
    Tuple nb = normalize(b);
    return (na.first == nb.first) && (na.second == nb.second);
}

static int contains(const Tuple *arr, size_t count, Tuple t)
{
    size_t i;
    for (i = 0; i < count; i++) {
        if (tuples_equal(arr[i], t)) {
            return 1;
        }
    }
    return 0;
}

static Tuple *tuple_intersection(const Tuple *list1, size_t n1,
                                 const Tuple *list2, size_t n2,
                                 size_t *out_count)
{
    Tuple *result;
    size_t i;
    size_t count = 0;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    if (list1 == NULL || list2 == NULL || n1 == 0 || n2 == 0) {
        return NULL;
    }

    result = malloc(n1 * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < n1; i++) {
        if (contains(list2, n2, list1[i]) &&
            !contains(result, count, list1[i])) {
            result[count] = normalize(list1[i]);
            count++;
        }
    }

    if (count == 0) {
        free(result);
        return NULL;
    }

    *out_count = count;
    return result;
}

static void print_tuples(const Tuple *arr, size_t count)
{
    size_t i;
    printf("{");
    for (i = 0; i < count; i++) {
        printf("(%d, %d)", arr[i].first, arr[i].second);
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void)
{
    Tuple list1[] = { {3, 4}, {5, 6}, {9, 10}, {4, 5} };
    Tuple list2[] = { {5, 4}, {3, 4}, {6, 5}, {9, 11} };
    size_t n1 = sizeof(list1) / sizeof(list1[0]);
    size_t n2 = sizeof(list2) / sizeof(list2[0]);
    size_t result_count = 0;
    Tuple *result;

    result = tuple_intersection(list1, n1, list2, n2, &result_count);

    if (result != NULL) {
        printf("Intersection: ");
        print_tuples(result, result_count);
        free(result);
        result = NULL;
    } else {
        printf("Intersection is empty or an error occurred.\n");
    }

    return EXIT_SUCCESS;
}