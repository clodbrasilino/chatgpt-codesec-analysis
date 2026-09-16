#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Tuple {
    int *elements;
    size_t size;
};

struct UnionResult {
    int *elements;
    size_t size;
};

struct UnionResult get_union(const struct Tuple *tuples, size_t num_tuples) {
    struct UnionResult result = {NULL, 0};
    
    if (!tuples || num_tuples == 0) {
        return result;
    }

    size_t total_elements = 0;
    for (size_t i = 0; i < num_tuples; ++i) {
        if (tuples[i].elements) {
            total_elements += tuples[i].size;
        }
    }

    if (total_elements == 0) {
        return result;
    }

    int *temp = (int *)malloc(total_elements * sizeof(int));
    if (!temp) {
        return result;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < num_tuples; ++i) {
        const struct Tuple *current_tuple = &tuples[i];
        if (!current_tuple->elements) {
            continue;
        }

        for (size_t j = 0; j < current_tuple->size; ++j) {
            int current_val = current_tuple->elements[j];
            bool is_duplicate = false;
            
            for (size_t k = 0; k < unique_count; ++k) {
                if (temp[k] == current_val) {
                    is_duplicate = true;
                    break;
                }
            }
            
            if (!is_duplicate) {
                temp[unique_count++] = current_val;
            }
        }
    }

    if (unique_count > 0) {
        result.elements = (int *)malloc(unique_count * sizeof(int));
        if (result.elements) {
            result.size = unique_count;
            for (size_t i = 0; i < unique_count; ++i) {
                result.elements[i] = temp[i];
            }
        }
    }

    free(temp);
    return result;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4};
    int arr2[] = {3, 4, 5, 6};
    int arr3[] = {6, 7, 8, 1};

    /* Possible weaknesses found:
     *  Variable 'tuples' can be declared as const array [constVariable]
     */
    struct Tuple tuples[3] = {
        {arr1, sizeof(arr1) / sizeof(arr1[0])},
        {arr2, sizeof(arr2) / sizeof(arr2[0])},
        {arr3, sizeof(arr3) / sizeof(arr3[0])}
    };

    struct UnionResult result = get_union(tuples, 3);

    if (result.elements) {
        for (size_t i = 0; i < result.size; ++i) {
            printf("%d ", result.elements[i]);
        }
        printf("\n");
        free(result.elements);
    }

    return 0;
}