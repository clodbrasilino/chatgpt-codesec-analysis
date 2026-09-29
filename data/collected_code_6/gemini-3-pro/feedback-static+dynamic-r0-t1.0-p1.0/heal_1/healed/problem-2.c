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
    for (size_t i = 0; i < size1; ++i) {
        for (size_t j = 0; j < size2; ++j) {
            if (list1[i].x == list2[j].x && list1[i].y == list2[j].y) {
                int already_added = 0;
                for (size_t k = 0; k < count; ++k) {
                    if (result[k].x == list1[i].x && result[k].y == list1[i].y) {
                        already_added = 1;
                        break;
                    }
                }
                if (!already_added) {
                    result[count++] = list1[i];
                }
                break;
            }
        }
    }

    if (count > 0) {
        Tuple* resized_result = (Tuple*)realloc(result, count * sizeof(Tuple));
        if (resized_result) {
            result = resized_result;
        }
        *out_list = result;
        *out_size = count;
    } else {
        free(result);
    }

    return 0;
}

int main(void) {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}, {1, 2}};
    Tuple list2[] = {{7, 8}, {1, 2}, {9, 0}, {3, 4}};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    
    Tuple* out_list = NULL;
    size_t out_size = 0;

    if (find_similar_tuples(list1, size1, list2, size2, &out_list, &out_size) == 0) {
        for (size_t i = 0; i < out_size; i++) {
            printf("{%d, %d}\n", out_list[i].x, out_list[i].y);
        }
        
        if (out_list) {
            free(out_list);
        }
    }

    return 0;
}