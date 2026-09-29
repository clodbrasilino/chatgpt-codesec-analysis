#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Tuple;

int compare_ints(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

int* find_similar_elements(Tuple* list1, int size1, Tuple* list2, int size2, int* result_size) {
    if (list1 == NULL || list2 == NULL || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = -1;
        }
        return NULL;
    }

    if (size1 <= 0 || size2 <= 0) {
        *result_size = 0;
        return NULL;
    }

    int* arr1 = (int*)malloc(size1 * sizeof(int));
    int* arr2 = (int*)malloc(size2 * sizeof(int));
    if (arr1 == NULL || arr2 == NULL) {
        free(arr1);
        free(arr2);
        *result_size = -1;
        return NULL;
    }

    for (int i = 0; i < size1; i++) {
        arr1[i] = list1[i].value;
    }
    for (int i = 0; i < size2; i++) {
        arr2[i] = list2[i].value;
    }

    qsort(arr1, size1, sizeof(int), compare_ints);
    qsort(arr2, size2, sizeof(int), compare_ints);

    int max_size = size1 < size2 ? size1 : size2;
    int* temp_result = (int*)malloc(max_size * sizeof(int));
    if (temp_result == NULL) {
        free(arr1);
        free(arr2);
        *result_size = -1;
        return NULL;
    }

    int i = 0, j = 0, count = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            i++;
        } else if (arr1[i] > arr2[j]) {
            j++;
        } else {
            if (count == 0 || temp_result[count - 1] != arr1[i]) {
                temp_result[count] = arr1[i];
                count++;
            }
            i++;
            j++;
        }
    }

    free(arr1);
    free(arr2);

    if (count == 0) {
        free(temp_result);
        *result_size = 0;
        return NULL;
    }

    int* final_result = (int*)realloc(temp_result, count * sizeof(int));
    if (final_result == NULL) {
        free(temp_result);
        *result_size = -1;
        return NULL;
    }

    *result_size = count;
    return final_result;
}

int main(void) {
    Tuple list1[] = {{4}, {1}, {5}, {2}, {3}};
    Tuple list2[] = {{5}, {6}, {4}, {7}, {3}};
    int result_size = 0;
    
    int* similar = find_similar_elements(list1, 5, list2, 5, &result_size);
    
    if (result_size == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    if (similar == NULL) {
        printf("[]\n");
        return 0;
    }
    
    printf("[");
    for (int i = 0; i < result_size; i++) {
        printf("%d", similar[i]);
        if (i < result_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    
    free(similar);
    return 0;
}