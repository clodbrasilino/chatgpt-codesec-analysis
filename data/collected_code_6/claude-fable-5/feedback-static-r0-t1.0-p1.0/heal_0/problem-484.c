#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int tuples_equal(const Tuple *a, const Tuple *b)
{
    return (a->first == b->first) && (a->second == b->second);
}

static Tuple *remove_matching_tuples(const Tuple *list1, size_t len1,
                                     const Tuple *list2, size_t len2,
                                     size_t *out_len)
{
    Tuple *result = NULL;
    size_t count = 0;
    size_t i;
    size_t j;

    if (out_len == NULL) {
        return NULL;
    }

    *out_len = 0;

    if (list1 == NULL || len1 == 0) {
        return NULL;
    }

    result = malloc(len1 * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len1; i++) {
        int matched = 0;
        if (list2 != NULL) {
            for (j = 0; j < len2; j++) {
                if (tuples_equal(&list1[i], &list2[j])) {
                    matched = 1;
                    break;
                }
            }
        }
        if (!matched) {
            result[count] = list1[i];
            count++;
        }
    }

    if (count == 0) {
        free(result);
        return NULL;
    }

    if (count < len1) {
        Tuple *shrunk = realloc(result, count * sizeof(Tuple));
        if (shrunk != NULL) {
            result = shrunk;
        }
    }

    *out_len = count;
    return result;
}

static void print_tuples(const Tuple *list, size_t len)
{
    size_t i;

    if (list == NULL || len == 0) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (i = 0; i < len; i++) {
        printf("(%d, %d)", list[i].first, list[i].second);
        if (i + 1 < len) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    Tuple list1[] = { {1, 2}, {3, 4}, {5, 6}, {7, 8} };
    Tuple list2[] = { {3, 4}, {7, 8}, {9, 10} };
    size_t len1 = sizeof(list1) / sizeof(list1[0]);
    size_t len2 = sizeof(list2) / sizeof(list2[0]);
    size_t result_len = 0;
    Tuple *result = NULL;

    printf("List 1: ");
    print_tuples(list1, len1);
    printf("List 2: ");
    print_tuples(list2, len2);

    result = remove_matching_tuples(list1, len1, list2, len2, &result_len);

    printf("Result: ");
    print_tuples(result, result_len);

    free(result);

    return EXIT_SUCCESS;
}