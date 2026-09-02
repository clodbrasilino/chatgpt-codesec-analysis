#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int contains_value(const int *arr, size_t size, int value) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

Tuple *remove_matching_tuples(const Tuple *tuple1, const Tuple *tuple2, size_t *result_size) {
    if (result_size == NULL) {
        return NULL;
    }

    *result_size = 0;

    if (tuple1 == NULL || tuple2 == NULL ||
        tuple1->data == NULL || tuple2->data == NULL ||
        tuple1->size % 2 != 0 || tuple2->size % 2 != 0) {
        return NULL;
    }

    size_t pair_count = tuple1->size / 2;
    size_t tuple2_pairs = tuple2->size / 2;
    size_t count = 0;

    int *result_data = (int *)malloc(tuple1->size * sizeof(int));
    if (result_data == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < pair_count; i++) {
        int val1 = tuple1->data[2 * i];
        int val2 = tuple1->data[2 * i + 1];
        int found = 0;

        for (size_t j = 0; j < tuple2_pairs; j++) {
            if (tuple2->data[2 * j] == val1 && tuple2->data[2 * j + 1] == val2) {
                found = 1;
                break;
            }
        }

        if (!found) {
            result_data[2 * count] = val1;
            result_data[2 * count + 1] = val2;
            count++;
        }
    }

    if (count == 0) {
        free(result_data);
        return NULL;
    }

    int *temp = (int *)realloc(result_data, 2 * count * sizeof(int));
    if (temp == NULL) {
        free(result_data);
        return NULL;
    }
    result_data = temp;

    Tuple *result = (Tuple *)malloc(sizeof(Tuple));
    if (result == NULL) {
        free(result_data);
        return NULL;
    }

    result->data = result_data;
    result->size = 2 * count;
    *result_size = 2 * count;

    return result;
}

int main(void) {
    int data1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int data2[] = {3, 4, 7, 8, 9, 10};
    Tuple tuple1 = {data1, 8};
    Tuple tuple2 = {data2, 6};

    size_t result_size;
    Tuple *result = remove_matching_tuples(&tuple1, &tuple2, &result_size);

    if (result != NULL) {
        printf("Result tuple: ");
        for (size_t i = 0; i < result->size; i += 2) {
            printf("(%d, %d) ", result->data[i], result->data[i + 1]);
        }
        printf("\n");
        free(result->data);
        free(result);
    } else {
        printf("No matching tuples removed\n");
    }

    return 0;
}