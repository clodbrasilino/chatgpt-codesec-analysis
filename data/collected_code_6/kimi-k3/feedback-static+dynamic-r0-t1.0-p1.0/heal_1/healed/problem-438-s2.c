#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} TupleArray;

int init_tuple_array(TupleArray *arr, size_t initial_capacity) {
    if (arr == NULL || initial_capacity == 0) {
        return -1;
    }
    arr->data = (Tuple *)malloc(initial_capacity * sizeof(Tuple));
    if (arr->data == NULL) {
        return -1;
    }
    arr->size = 0;
    arr->capacity = initial_capacity;
    return 0;
}

void free_tuple_array(TupleArray *arr) {
    if (arr != NULL) {
        free(arr->data);
        arr->data = NULL;
        arr->size = 0;
        arr->capacity = 0;
    }
}

int add_tuple(TupleArray *arr, int first, int second) {
    if (arr == NULL) {
        return -1;
    }
    if (arr->size >= arr->capacity) {
        size_t new_capacity = arr->capacity * 2;
        Tuple *new_data = (Tuple *)realloc(arr->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return -1;
        }
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    arr->data[arr->size].first = first;
    arr->data[arr->size].second = second;
    arr->size++;
    return 0;
}

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->first != tb->first) {
        return ta->first - tb->first;
    }
    return ta->second - tb->second;
}

size_t count_bidirectional_pairs(TupleArray *arr) {
    if (arr == NULL || arr->size == 0) {
        return 0;
    }
    
    qsort(arr->data, arr->size, sizeof(Tuple), compare_tuples);
    
    size_t count = 0;
    size_t i = 0;
    
    while (i < arr->size) {
        size_t j = i;
        while (j < arr->size && 
               arr->data[j].first == arr->data[i].first && 
               arr->data[j].second == arr->data[i].second) {
            j++;
        }
        
        size_t freq_a = j - i;
        int a = arr->data[i].first;
        int b = arr->data[i].second;
        
        if (a != b) {
            Tuple target = {b, a};
            const Tuple *found = (const Tuple *)bsearch(&target, arr->data, arr->size, 
                                                        sizeof(Tuple), compare_tuples);
            if (found != NULL) {
                size_t k = (size_t)(found - arr->data);
                size_t start = k;
                while (start > 0 && 
                       arr->data[start - 1].first == b && 
                       arr->data[start - 1].second == a) {
                    start--;
                }
                size_t end = k;
                while (end < arr->size && 
                       arr->data[end].first == b && 
                       arr->data[end].second == a) {
                    end++;
                }
                size_t freq_b = end - start;
                count += freq_a * freq_b;
            }
        }
        
        i = j;
    }
    
    return count / 2;
}

int main(void) {
    TupleArray arr;
    
    if (init_tuple_array(&arr, 10) != 0) {
        fprintf(stderr, "Failed to initialize array\n");
        return EXIT_FAILURE;
    }
    
    if (add_tuple(&arr, 1, 2) != 0 ||
        add_tuple(&arr, 2, 1) != 0 ||
        add_tuple(&arr, 3, 4) != 0 ||
        add_tuple(&arr, 4, 3) != 0 ||
        add_tuple(&arr, 5, 6) != 0 ||
        add_tuple(&arr, 1, 2) != 0 ||
        add_tuple(&arr, 2, 1) != 0) {
        fprintf(stderr, "Failed to add tuples\n");
        free_tuple_array(&arr);
        return EXIT_FAILURE;
    }
    
    size_t result = count_bidirectional_pairs(&arr);
    printf("Bidirectional pairs count: %zu\n", result);
    
    free_tuple_array(&arr);
    return EXIT_SUCCESS;
}