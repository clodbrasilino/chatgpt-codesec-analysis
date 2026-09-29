#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} List;

typedef struct {
    List *sublists;
    size_t count;
} NestedList;

typedef struct {
    int **results;
    size_t *result_sizes;
    size_t count;
} MatchResult;

static int contains(const int *arr, size_t size, int value)
{
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

static void free_match_result(MatchResult *res)
{
    if (res == NULL) {
        return;
    }
    if (res->results != NULL) {
        for (size_t i = 0; i < res->count; i++) {
            free(res->results[i]);
        }
        free(res->results);
    }
    free(res->result_sizes);
    free(res);
}

static MatchResult *find_nested_in_list(const NestedList *nested, const int *other, size_t other_size)
{
    MatchResult *res;

    if (nested == NULL || other == NULL) {
        return NULL;
    }

    res = malloc(sizeof(MatchResult));
    if (res == NULL) {
        return NULL;
    }

    res->count = nested->count;
    res->results = calloc(nested->count, sizeof(int *));
    res->result_sizes = calloc(nested->count, sizeof(size_t));

    if (res->results == NULL || res->result_sizes == NULL) {
        free_match_result(res);
        return NULL;
    }

    for (size_t i = 0; i < nested->count; i++) {
        size_t match_count = 0;
        const List *sub = &nested->sublists[i];

        for (size_t j = 0; j < sub->size; j++) {
            if (contains(other, other_size, sub->data[j])) {
                match_count++;
            }
        }

        if (match_count > 0) {
            size_t k = 0;
            res->results[i] = malloc(match_count * sizeof(int));
            if (res->results[i] == NULL) {
                free_match_result(res);
                return NULL;
            }
            for (size_t j = 0; j < sub->size; j++) {
                if (contains(other, other_size, sub->data[j])) {
                    res->results[i][k] = sub->data[j];
                    k++;
                }
            }
            res->result_sizes[i] = match_count;
        } else {
            res->results[i] = NULL;
            res->result_sizes[i] = 0;
        }
    }

    return res;
}

int main(void)
{
    int sub1[] = {1, 2, 3};
    int sub2[] = {4, 5, 6};
    int sub3[] = {7, 8, 9, 10};
    int other[] = {2, 5, 7, 10, 11};

    List sublists[3];
    NestedList nested;
    MatchResult *res;

    sublists[0].data = sub1;
    sublists[0].size = sizeof(sub1) / sizeof(sub1[0]);
    sublists[1].data = sub2;
    sublists[1].size = sizeof(sub2) / sizeof(sub2[0]);
    sublists[2].data = sub3;
    sublists[2].size = sizeof(sub3) / sizeof(sub3[0]);

    nested.sublists = sublists;
    nested.count = 3;

    res = find_nested_in_list(&nested, other, sizeof(other) / sizeof(other[0]));
    if (res == NULL) {
        fprintf(stderr, "Failed to compute matches\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < res->count; i++) {
        printf("Sublist %zu matches: [", i);
        for (size_t j = 0; j < res->result_sizes[i]; j++) {
            printf("%d", res->results[i][j]);
            if (j + 1 < res->result_sizes[i]) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    free_match_result(res);
    return EXIT_SUCCESS;
}