#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

bool are_tuples_equal(Tuple a, Tuple b) {
    return (a.first == b.first && a.second == b.second) ||
           (a.first == b.second && a.second == b.first);
}

Tuple* get_tuple_intersection(const Tuple* list1, size_t size1, const Tuple* list2, size_t size2, size_t* out_size) {
    if (!out_size) {
        return NULL;
    }
    
    *out_size = 0;

    if (!list1 || !list2 || size1 == 0 || size2 == 0) {
        return NULL;
    }

    size_t max_size = (size1 < size2) ? size1 : size2;
    Tuple* result = (Tuple*)malloc(max_size * sizeof(Tuple));
    if (!result) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size1; i++) {
        bool found_in_list2 = false;
        for (size_t j = 0; j < size2; j++) {
            if (are_tuples_equal(list1[i], list2[j])) {
                found_in_list2 = true;
                break;
            }
        }

        if (found_in_list2) {
            bool already_in_result = false;
            for (size_t k = 0; k < count; k++) {
                if (are_tuples_equal(list1[i], result[k])) {
                    already_in_result = true;
                    break;
                }
            }
            if (!already_in_result) {
                result[count++] = list1[i];
            }
        }
    }

    if (count == 0) {
        free(result);
        return NULL;
    }

    *out_size = count;
    Tuple* shrunk_result = (Tuple*)realloc(result, count * sizeof(Tuple));
    
    return shrunk_result ? shrunk_result : result;
}

int main(void) {
    Tuple list1[] = {{3, 4}, {5, 6}, {7, 8}};
    Tuple list2[] = {{5, 4}, {4, 3}, {6, 5}};
    
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t out_size = 0;

    Tuple* result = get_tuple_intersection(list1, size1, list2, size2, &out_size);

    if (result) {
        for (size_t i = 0; i < out_size; i++) {
            printf("(%d, %d)\n", result[i].first, result[i].second);
        }
        free(result);
    }

    return 0;
}