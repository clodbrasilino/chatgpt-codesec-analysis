#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int a;
    int b;
} Tuple;

bool are_tuples_equal_unordered(Tuple t1, Tuple t2) {
    return (t1.a == t2.a && t1.b == t2.b) || (t1.a == t2.b && t1.b == t2.a);
}

bool is_tuple_in_list(Tuple t, const Tuple* list, size_t size) {
    if (!list) {
        return false;
    }
    for (size_t i = 0; i < size; i++) {
        if (are_tuples_equal_unordered(t, list[i])) {
            return true;
        }
    }
    return false;
}

Tuple* get_tuple_intersection(const Tuple* list1, size_t size1, const Tuple* list2, size_t size2, size_t* out_size) {
    if (!out_size) {
        return NULL;
    }
    
    *out_size = 0;
    
    if (!list1 || size1 == 0 || !list2 || size2 == 0) {
        return NULL;
    }

    size_t max_size = size1 < size2 ? size1 : size2;
    Tuple* result = (Tuple*)malloc(max_size * sizeof(Tuple));
    if (!result) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size1; i++) {
        if (is_tuple_in_list(list1[i], list2, size2)) {
            if (!is_tuple_in_list(list1[i], result, count)) {
                result[count++] = list1[i];
            }
        }
    }

    if (count == 0) {
        free(result);
        return NULL;
    }

    Tuple* exact_result = (Tuple*)realloc(result, count * sizeof(Tuple));
    if (!exact_result) {
        *out_size = count;
        return result;
    }

    *out_size = count;
    return exact_result;
}

int main(void) {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {4, 3}};
    Tuple list2[] = {{4, 3}, {2, 1}, {9, 10}, {8, 7}};
    
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t out_size = 0;

    Tuple* intersection = get_tuple_intersection(list1, size1, list2, size2, &out_size);

    if (intersection) {
        for (size_t i = 0; i < out_size; i++) {
            printf("(%d, %d)\n", intersection[i].a, intersection[i].b);
        }
        free(intersection);
    }

    return 0;
}