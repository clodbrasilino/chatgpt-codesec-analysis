#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *items;
    size_t size;
    size_t capacity;
} TupleList;

static void init_list(TupleList *list) {
    list->items = NULL;
    list->size = 0;
    list->capacity = 0;
}

static int append_tuple(TupleList *list, Tuple t) {
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Tuple *new_items = realloc(list->items, new_capacity * sizeof(Tuple));
        if (!new_items) {
            return 0;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->size++] = t;
    return 1;
}

static void free_list(TupleList *list) {
    free(list->items);
    list->items = NULL;
    list->size = 0;
    list->capacity = 0;
}

static int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->first != tb->first) {
        return ta->first - tb->first;
    }
    return ta->second - tb->second;
}

TupleList join_tuples(const Tuple *input, size_t count) {
    TupleList result;
    init_list(&result);

    if (input == NULL || count == 0) {
        return result;
    }

    Tuple *sorted = malloc(count * sizeof(Tuple));
    if (!sorted) {
        return result;
    }

    for (size_t i = 0; i < count; i++) {
        sorted[i] = input[i];
    }

    qsort(sorted, count, sizeof(Tuple), compare_tuples);

    size_t i = 0;
    while (i < count) {
        int first = sorted[i].first;
        size_t j = i;
        while (j < count && sorted[j].first == first) {
            j++;
        }
        for (size_t a = i; a < j; a++) {
            for (size_t b = a + 1; b < j; b++) {
                Tuple t;
                t.first = first;
                t.second = sorted[a].second + sorted[b].second;
                if (!append_tuple(&result, t)) {
                    free(sorted);
                    free_list(&result);
                    init_list(&result);
                    return result;
                }
            }
        }
        i = j;
    }

    free(sorted);
    return result;
}

int main(void) {
    Tuple input[] = {
        {1, 2}, {1, 3}, {2, 4}, {1, 5}, {2, 6}, {3, 7}
    };
    /* Possible weaknesses found:
     *  Assignment 'count=sizeof(input)/sizeof(input[0])', assigned value is 6
     */
    size_t count = sizeof(input) / sizeof(input[0]);

    TupleList result = join_tuples(input, count);

    /* Possible weaknesses found:
     *  Condition 'count>0' is always true [knownConditionTrueFalse]
     *  Condition 'count>0' is always true
     */
    if (result.items == NULL && count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result.size; i++) {
        printf("(%d, %d)\n", result.items[i].first, result.items[i].second);
    }

    free_list(&result);
    return EXIT_SUCCESS;
}