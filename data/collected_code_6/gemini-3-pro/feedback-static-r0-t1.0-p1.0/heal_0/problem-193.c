#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

Tuple* remove_duplicates(const Tuple *input) {
    if (input == NULL || input->data == NULL) {
        return NULL;
    }

    Tuple *result = (Tuple*)malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    if (input->size == 0) {
        result->data = NULL;
        result->size = 0;
        return result;
    }

    result->data = (int*)malloc(input->size * sizeof(int));
    if (result->data == NULL) {
        free(result);
        return NULL;
    }

    size_t unique_count = 0;
    for (size_t i = 0; i < input->size; i++) {
        int is_duplicate = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (input->data[i] == result->data[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            result->data[unique_count++] = input->data[i];
        }
    }

    result->size = unique_count;

    if (unique_count < input->size) {
        int *resized_data = (int*)realloc(result->data, unique_count * sizeof(int));
        if (resized_data != NULL) {
            result->data = resized_data;
        } else if (unique_count == 0) {
            free(result->data);
            result->data = NULL;
        }
    }

    return result;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        if (t->data != NULL) {
            free(t->data);
        }
        free(t);
    }
}

int main(void) {
    int arr[] = {1, 2, 2, 3, 4, 4, 4, 5, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    Tuple input_tuple;
    input_tuple.data = arr;
    input_tuple.size = size;

    Tuple *unique_tuple = remove_duplicates(&input_tuple);

    if (unique_tuple != NULL) {
        for (size_t i = 0; i < unique_tuple->size; i++) {
            printf("%d ", unique_tuple->data[i]);
        }
        printf("\n");
        free_tuple(unique_tuple);
    }

    return 0;
}