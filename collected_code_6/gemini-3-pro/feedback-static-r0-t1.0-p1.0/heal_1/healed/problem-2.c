#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

int find_similar_tuples(const Tuple* list1, size_t size1, const Tuple* list2, size_t size2, Tuple** out_list, size_t* out_size) {
    if (!list1 || !list2 || !out_list || !out_size) {
        return -1;
    }

    *out_list = NULL;
    *out_size = 0;

    if (size1 == 0 || size2 == 0) {
        return 0;
    }

    size_t max_possible_size = (size1 < size2) ? size1 : size2;
    Tuple* result = (Tuple*)malloc(max_possible_size * sizeof(Tuple));
    
    if (!result) {
        return -1;
    }

    size_t count = 0;
    for (size_t i = 0; i < size1; i++) {
        for (size_t j = 0; j < size2; j++) {
            if (list1[i].x == list2[j].x && list1[i].y == list2[j].y) {
                result[count++] = list1[i];
                break;
            }
        }
    }

    *out_size = count;
    
    if (count > 0) {
        Tuple* resized_result = (Tuple*)realloc(result, count * sizeof(Tuple));
        if (resized_result) {
            *out_list = resized_result;
        } else {
            *out_list = result;
        }
    } else {
        free(result);
        *out_list = NULL;
    }

    return 0;
}

int main(void) {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple list2[] = {{3, 4}, {7, 8}, {1, 2}};
    
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    
    Tuple* similar_tuples = NULL;
    size_t similar_size = 0;
    
    if (find_similar_tuples(list1, size1, list2, size2, &similar_tuples, &similar_size) == 0) {
        for (size_t i = 0; i < similar_size; i++) {
            printf("{%d, %d}\n", similar_tuples[i].x, similar_tuples[i].y);
        }
        free(similar_tuples);
    }
    
    return 0;
}