#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

typedef struct {
    int *min_elements;
    int *max_elements;
    int k;
} Result;

int compare_asc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compare_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

Result extract_min_max_k(const Tuple *tuple, int k) {
    Result result;
    result.min_elements = NULL;
    result.max_elements = NULL;
    result.k = 0;

    if (tuple == NULL || tuple->data == NULL || tuple->size <= 0 || k <= 0) {
        return result;
    }

    if (k > tuple->size) {
        k = tuple->size;
    }

    int *sorted_asc = (int*)malloc(tuple->size * sizeof(int));
    int *sorted_desc = (int*)malloc(tuple->size * sizeof(int));
    
    if (sorted_asc == NULL || sorted_desc == NULL) {
        free(sorted_asc);
        free(sorted_desc);
        return result;
    }

    for (int i = 0; i < tuple->size; i++) {
        sorted_asc[i] = tuple->data[i];
        sorted_desc[i] = tuple->data[i];
    }

    qsort(sorted_asc, tuple->size, sizeof(int), compare_asc);
    qsort(sorted_desc, tuple->size, sizeof(int), compare_desc);

    result.min_elements = (int*)malloc(k * sizeof(int));
    result.max_elements = (int*)malloc(k * sizeof(int));

    if (result.min_elements == NULL || result.max_elements == NULL) {
        free(sorted_asc);
        free(sorted_desc);
        free(result.min_elements);
        free(result.max_elements);
        result.min_elements = NULL;
        result.max_elements = NULL;
        return result;
    }

    for (int i = 0; i < k; i++) {
        result.min_elements[i] = sorted_asc[i];
        result.max_elements[i] = sorted_desc[i];
    }

    result.k = k;

    free(sorted_asc);
    free(sorted_desc);

    return result;
}

void free_result(Result *result) {
    if (result != NULL) {
        free(result->min_elements);
        free(result->max_elements);
        result->min_elements = NULL;
        result->max_elements = NULL;
        result->k = 0;
    }
}

int main(void) {
    int test_data[] = {42, 11, 7, 21, 89, 15, 67, 3, 52, 28};
    Tuple tuple;
    tuple.data = test_data;
    tuple.size = sizeof(test_data) / sizeof(test_data[0]);

    int k = 3;
    Result result = extract_min_max_k(&tuple, k);

    if (result.min_elements != NULL && result.max_elements != NULL) {
        printf("Minimum %d elements: ", result.k);
        for (int i = 0; i < result.k; i++) {
            printf("%d ", result.min_elements[i]);
        }
        printf("\n");

        printf("Maximum %d elements: ", result.k);
        for (int i = 0; i < result.k; i++) {
            printf("%d ", result.max_elements[i]);
        }
        printf("\n");
    } else {
        printf("Failed to extract elements\n");
    }

    free_result(&result);

    return 0;
}