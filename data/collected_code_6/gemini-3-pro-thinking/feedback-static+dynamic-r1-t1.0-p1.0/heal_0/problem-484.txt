#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *data;
    size_t count;
} TupleArray;

bool tuples_equal(const Tuple *t1, const Tuple *t2) {
    if (!t1 || !t2) {
        return false;
    }
    return (t1->first == t2->first) && (t1->second == t2->second);
}

bool is_tuple_in_array(const Tuple *t, const TupleArray *arr) {
    if (!t || !arr || !arr->data) {
        return false;
    }
    for (size_t i = 0; i < arr->count; ++i) {
        if (tuples_equal(t, &arr->data[i])) {
            return true;
        }
    }
    return false;
}

TupleArray* remove_matching_tuples(const TupleArray *list1, const TupleArray *list2) {
    if (!list1 || !list2) {
        return NULL;
    }

    TupleArray *result = malloc(sizeof(TupleArray));
    if (!result) {
        return NULL;
    }

    size_t max_possible = list1->count + list2->count;
    if (max_possible == 0) {
        result->data = NULL;
        result->count = 0;
        return result;
    }

    result->data = malloc(max_possible * sizeof(Tuple));
    if (!result->data) {
        free(result);
        return NULL;
    }
    result->count = 0;

    for (size_t i = 0; i < list1->count; ++i) {
        if (!is_tuple_in_array(&list1->data[i], list2)) {
            result->data[result->count++] = list1->data[i];
        }
    }

    for (size_t i = 0; i < list2->count; ++i) {
        if (!is_tuple_in_array(&list2->data[i], list1)) {
            result->data[result->count++] = list2->data[i];
        }
    }

    if (result->count == 0) {
        free(result->data);
        result->data = NULL;
    } else if (result->count < max_possible) {
        Tuple *resized = realloc(result->data, result->count * sizeof(Tuple));
        if (resized) {
            result->data = resized;
        }
    }

    return result;
}

void free_tuple_array(TupleArray *arr) {
    if (arr) {
        free(arr->data);
        free(arr);
    }
}

int main(void) {
    Tuple data1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple data2[] = {{3, 4}, {9, 10}, {1, 2}, {11, 12}};

    TupleArray list1 = {data1, sizeof(data1) / sizeof(data1[0])};
    TupleArray list2 = {data2, sizeof(data2) / sizeof(data2[0])};

    TupleArray *result = remove_matching_tuples(&list1, &list2);
    if (!result) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < result->count; ++i) {
        printf("(%d, %d)\n", result->data[i].first, result->data[i].second);
    }

    free_tuple_array(result);
    return EXIT_SUCCESS;
}