#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int **data;
    size_t rows;
    size_t cols;
} TupleList;

typedef struct {
    int *data;
    size_t length;
} IntList;

TupleList *add_list_to_tuples(const TupleList *tuples, const IntList *list, int *error) {
    if (tuples == NULL || list == NULL || error == NULL) {
        if (error != NULL) *error = -1;
        return NULL;
    }

    if (list->length == 0 || tuples->rows == 0 || tuples->cols == 0) {
        *error = -2;
        return NULL;
    }

    if (list->length != tuples->cols) {
        *error = -3;
        return NULL;
    }

    TupleList *result = (TupleList *)malloc(sizeof(TupleList));
    if (result == NULL) {
        *error = -4;
        return NULL;
    }

    result->rows = tuples->rows;
    result->cols = tuples->cols;
    result->data = (int **)malloc(sizeof(int *) * result->rows);
    if (result->data == NULL) {
        free(result);
        *error = -4;
        return NULL;
    }

    for (size_t i = 0; i < result->rows; i++) {
        result->data[i] = (int *)malloc(sizeof(int) * result->cols);
        if (result->data[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result->data[j]);
            }
            free(result->data);
            free(result);
            *error = -4;
            return NULL;
        }
    }

    for (size_t i = 0; i < tuples->rows; i++) {
        for (size_t j = 0; j < tuples->cols; j++) {
            result->data[i][j] = tuples->data[i][j] + list->data[j];
        }
    }

    *error = 0;
    return result;
}

void free_tuple_list(TupleList *tuples) {
    if (tuples == NULL) return;
    for (size_t i = 0; i < tuples->rows; i++) {
        free(tuples->data[i]);
    }
    free(tuples->data);
    free(tuples);
}

int main(void) {
    int error = 0;
    size_t rows = 3;
    size_t cols = 4;

    TupleList *tuples = (TupleList *)malloc(sizeof(TupleList));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    tuples->rows = rows;
    tuples->cols = cols;
    tuples->data = (int **)malloc(sizeof(int *) * rows);
    if (tuples->data == NULL) {
        free(tuples);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int src[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    for (size_t i = 0; i < rows; i++) {
        tuples->data[i] = (int *)malloc(sizeof(int) * cols);
        if (tuples->data[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuples->data[j]);
            }
            free(tuples->data);
            free(tuples);
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        for (size_t j = 0; j < cols; j++) {
            tuples->data[i][j] = src[i][j];
        }
    }

    IntList *list = (IntList *)malloc(sizeof(IntList));
    if (list == NULL) {
        free_tuple_list(tuples);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    list->length = cols;
    list->data = (int *)malloc(sizeof(int) * cols);
    if (list->data == NULL) {
        free(list);
        free_tuple_list(tuples);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    const int list_values[4] = {10, 20, 30, 40};
    for (size_t i = 0; i < cols; i++) {
        list->data[i] = list_values[i];
    }

    TupleList *result = add_list_to_tuples(tuples, list, &error);
    if (error != 0 || result == NULL) {
        fprintf(stderr, "Error: %d\n", error);
        free(list->data);
        free(list);
        free_tuple_list(tuples);
        return 1;
    }

    for (size_t i = 0; i < result->rows; i++) {
        for (size_t j = 0; j < result->cols; j++) {
            printf("%d ", result->data[i][j]);
        }
        printf("\n");
    }

    free(list->data);
    free(list);
    free_tuple_list(tuples);
    free_tuple_list(result);

    return 0;
}