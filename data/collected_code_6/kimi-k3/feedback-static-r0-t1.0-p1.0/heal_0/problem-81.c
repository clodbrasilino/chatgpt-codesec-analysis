#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} IntTuple;

typedef struct {
    char **data;
    size_t size;
} StringTuple;

typedef struct {
    int first;
    char *second;
} ZippedPair;

typedef struct {
    ZippedPair *pairs;
    size_t size;
} ZippedResult;

IntTuple *create_int_tuple(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return NULL;
    }
    IntTuple *tuple = malloc(sizeof(IntTuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->data = malloc(size * sizeof(int));
    if (tuple->data == NULL) {
        free(tuple);
        return NULL;
    }
    memcpy(tuple->data, arr, size * sizeof(int));
    tuple->size = size;
    return tuple;
}

StringTuple *create_string_tuple(char **arr, size_t size) {
    if (arr == NULL || size == 0) {
        return NULL;
    }
    StringTuple *tuple = malloc(sizeof(StringTuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->data = malloc(size * sizeof(char *));
    if (tuple->data == NULL) {
        free(tuple);
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->data[j]);
            }
            free(tuple->data);
            free(tuple);
            return NULL;
        }
        tuple->data[i] = malloc(strlen(arr[i]) + 1);
        if (tuple->data[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->data[j]);
            }
            free(tuple->data);
            free(tuple);
            return NULL;
        }
        strcpy(tuple->data[i], arr[i]);
    }
    tuple->size = size;
    return tuple;
}

ZippedResult *zip_tuples(const IntTuple *tuple1, const StringTuple *tuple2) {
    if (tuple1 == NULL || tuple2 == NULL || tuple1->size != tuple2->size) {
        return NULL;
    }
    ZippedResult *result = malloc(sizeof(ZippedResult));
    if (result == NULL) {
        return NULL;
    }
    result->pairs = malloc(tuple1->size * sizeof(ZippedPair));
    if (result->pairs == NULL) {
        free(result);
        return NULL;
    }
    result->size = tuple1->size;
    for (size_t i = 0; i < result->size; i++) {
        result->pairs[i].first = tuple1->data[i];
        result->pairs[i].second = malloc(strlen(tuple2->data[i]) + 1);
        if (result->pairs[i].second == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result->pairs[j].second);
            }
            free(result->pairs);
            free(result);
            return NULL;
        }
        strcpy(result->pairs[i].second, tuple2->data[i]);
    }
    return result;
}

void free_int_tuple(IntTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->data);
        free(tuple);
    }
}

void free_string_tuple(StringTuple *tuple) {
    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->size; i++) {
            free(tuple->data[i]);
        }
        free(tuple->data);
        free(tuple);
    }
}

void free_zipped_result(ZippedResult *result) {
    if (result != NULL) {
        for (size_t i = 0; i < result->size; i++) {
            free(result->pairs[i].second);
        }
        free(result->pairs);
        free(result);
    }
}

int main(void) {
    int int_arr[] = {1, 2, 3, 4, 5};
    char *str_arr[] = {"apple", "banana", "cherry", "date", "elderberry"};
    size_t size = sizeof(int_arr) / sizeof(int_arr[0]);

    IntTuple *tuple1 = create_int_tuple(int_arr, size);
    if (tuple1 == NULL) {
        fprintf(stderr, "Failed to create integer tuple\n");
        return EXIT_FAILURE;
    }

    StringTuple *tuple2 = create_string_tuple(str_arr, size);
    if (tuple2 == NULL) {
        fprintf(stderr, "Failed to create string tuple\n");
        free_int_tuple(tuple1);
        return EXIT_FAILURE;
    }

    ZippedResult *zipped = zip_tuples(tuple1, tuple2);
    if (zipped == NULL) {
        fprintf(stderr, "Failed to zip tuples\n");
        free_string_tuple(tuple2);
        free_int_tuple(tuple1);
        return EXIT_FAILURE;
    }

    printf("Zipped pairs:\n");
    for (size_t i = 0; i < zipped->size; i++) {
        printf("(%d, %s)\n", zipped->pairs[i].first, zipped->pairs[i].second);
    }

    free_zipped_result(zipped);
    free_string_tuple(tuple2);
    free_int_tuple(tuple1);

    return EXIT_SUCCESS;
}