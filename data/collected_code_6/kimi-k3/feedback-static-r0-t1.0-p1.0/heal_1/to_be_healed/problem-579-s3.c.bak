#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

void tuple_init(Tuple *t, size_t size) {
    t->size = size;
    t->data = (int *)malloc(size * sizeof(int));
    if (t->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void tuple_free(Tuple *t) {
    if (t->data != NULL) {
        free(t->data);
        t->data = NULL;
    }
    t->size = 0;
}

int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int binary_search(const int *arr, size_t size, int target) {
    size_t left = 0;
    size_t right = size;
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return 0;
}

size_t find_dissimilar(const Tuple *t1, const Tuple *t2, int **result) {
    /* Possible weaknesses found:
     *  Assuming that condition 'result==NULL' is not redundant
     */
    if (t1 == NULL || t2 == NULL || result == NULL || t1->data == NULL || t2->data == NULL) {
        /* Possible weaknesses found:
         *  Null pointer dereference
         *  Either the condition 'result==NULL' is redundant or there is possible null pointer dereference: result. [nullPointerRedundantCheck]
         */
        *result = NULL;
        return 0;
    }
    
    size_t max_size = t1->size + t2->size;
    int *temp = (int *)malloc(max_size * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    int *sorted1 = (int *)malloc(t1->size * sizeof(int));
    int *sorted2 = (int *)malloc(t2->size * sizeof(int));
    
    if (sorted1 == NULL || sorted2 == NULL) {
        free(temp);
        free(sorted1);
        free(sorted2);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    memcpy(sorted1, t1->data, t1->size * sizeof(int));
    memcpy(sorted2, t2->data, t2->size * sizeof(int));
    
    qsort(sorted1, t1->size, sizeof(int), compare_ints);
    qsort(sorted2, t2->size, sizeof(int), compare_ints);
    
    size_t count = 0;
    
    for (size_t i = 0; i < t1->size; i++) {
        if (!binary_search(sorted2, t2->size, t1->data[i])) {
            temp[count++] = t1->data[i];
        }
    }
    
    for (size_t i = 0; i < t2->size; i++) {
        if (!binary_search(sorted1, t1->size, t2->data[i])) {
            temp[count++] = t2->data[i];
        }
    }
    
    free(sorted1);
    free(sorted2);
    
    if (count == 0) {
        free(temp);
        *result = NULL;
        return 0;
    }
    
    int *final_result = (int *)realloc(temp, count * sizeof(int));
    if (final_result == NULL) {
        *result = temp;
    } else {
        *result = final_result;
    }
    
    return count;
}

int main(void) {
    Tuple t1, t2;
    int *result = NULL;
    
    tuple_init(&t1, 5);
    tuple_init(&t2, 4);
    
    t1.data[0] = 3;
    t1.data[1] = 4;
    t1.data[2] = 5;
    t1.data[3] = 6;
    t1.data[4] = 7;
    
    t2.data[0] = 5;
    t2.data[1] = 6;
    t2.data[2] = 8;
    t2.data[3] = 9;
    
    size_t result_size = find_dissimilar(&t1, &t2, &result);
    
    printf("Dissimilar elements: ");
    for (size_t i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    if (result != NULL) {
        free(result);
    }
    
    tuple_free(&t1);
    tuple_free(&t2);
    
    return 0;
}