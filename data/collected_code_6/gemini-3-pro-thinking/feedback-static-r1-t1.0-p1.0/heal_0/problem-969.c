#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

TupleList create_tuple_list(size_t capacity) {
    TupleList list;
    list.count = 0;
    list.capacity = capacity;
    list.tuples = NULL;

    if (capacity > 0) {
        list.tuples = malloc(capacity * sizeof(Tuple));
        if (!list.tuples) {
            list.capacity = 0;
        }
    }
    return list;
}

void free_tuple_list(TupleList *list) {
    if (!list || !list->tuples) {
        return;
    }
    for (size_t i = 0; i < list->count; ++i) {
        free(list->tuples[i].data);
        list->tuples[i].data = NULL;
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
    list->capacity = 0;
}

bool add_tuple(TupleList *list, const int *arr, size_t size) {
    if (!list || !list->tuples || list->count >= list->capacity) {
        return false;
    }
    
    int *data = malloc(size * sizeof(int));
    if (!data) {
        return false;
    }
    
    for (size_t i = 0; i < size; ++i) {
        data[i] = arr[i];
    }
    
    list->tuples[list->count].data = data;
    list->tuples[list->count].size = size;
    list->count++;
    
    return true;
}

TupleList join_tuples(const TupleList *input) {
    TupleList result = create_tuple_list(0);
    
    if (!input || !input->tuples || input->count == 0) {
        return result;
    }

    result = create_tuple_list(input->count);
    if (!result.tuples) {
        return result;
    }

    for (size_t i = 0; i < input->count; ++i) {
        const Tuple *current = &input->tuples[i];
        if (current->size == 0) {
            continue;
        }

        bool found = false;
        for (size_t j = 0; j < result.count; ++j) {
            Tuple *res_tuple = &result.tuples[j];
            
            if (res_tuple->size > 0 && res_tuple->data[0] == current->data[0]) {
                size_t new_size = res_tuple->size + current->size - 1;
                int *new_data = realloc(res_tuple->data, new_size * sizeof(int));
                
                if (!new_data) {
                    free_tuple_list(&result);
                    return result;
                }
                
                res_tuple->data = new_data;
                for (size_t k = 1; k < current->size; ++k) {
                    res_tuple->data[res_tuple->size + k - 1] = current->data[k];
                }
                res_tuple->size = new_size;
                found = true;
                break;
            }
        }

        if (!found) {
            int *new_data = malloc(current->size * sizeof(int));
            if (!new_data) {
                free_tuple_list(&result);
                return result;
            }
            
            for (size_t k = 0; k < current->size; ++k) {
                new_data[k] = current->data[k];
            }
            
            result.tuples[result.count].data = new_data;
            result.tuples[result.count].size = current->size;
            result.count++;
        }
    }
    
    return result;
}

int main(void) {
    TupleList input = create_tuple_list(4);
    if (!input.tuples) {
        return EXIT_FAILURE;
    }

    const int arr1[] = {1, 2};
    const int arr2[] = {1, 3};
    const int arr3[] = {2, 4};
    const int arr4[] = {1, 5};

    if (!add_tuple(&input, arr1, sizeof(arr1) / sizeof(arr1[0])) ||
        !add_tuple(&input, arr2, sizeof(arr2) / sizeof(arr2[0])) ||
        !add_tuple(&input, arr3, sizeof(arr3) / sizeof(arr3[0])) ||
        !add_tuple(&input, arr4, sizeof(arr4) / sizeof(arr4[0]))) {
        free_tuple_list(&input);
        return EXIT_FAILURE;
    }

    TupleList joined = join_tuples(&input);
    if (!joined.tuples && input.count > 0) {
        free_tuple_list(&input);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < joined.count; ++i) {
        printf("(");
        for (size_t j = 0; j < joined.tuples[i].size; ++j) {
            printf("%d", joined.tuples[i].data[j]);
            if (j < joined.tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_tuple_list(&input);
    free_tuple_list(&joined);

    return EXIT_SUCCESS;
}