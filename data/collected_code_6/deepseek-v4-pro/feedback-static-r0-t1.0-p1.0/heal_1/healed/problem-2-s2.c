#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

int contains(const int *arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

int *find_similar_elements(Tuple list1, Tuple list2, int *result_size) {
    if (list1.data == NULL || list2.data == NULL || list1.size <= 0 || list2.size <= 0) {
        *result_size = 0;
        return NULL;
    }

    int max_size = list1.size < list2.size ? list1.size : list2.size;
    int *result = (int *)malloc(max_size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < list1.size; i++) {
        for (int j = 0; j < list2.size; j++) {
            if (list1.data[i] == list2.data[j] && !contains(result, count, list1.data[i])) {
                result[count++] = list1.data[i];
                break;
            }
        }
    }

    if (count == 0) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    int *final_result = (int *)realloc(result, count * sizeof(int));
    if (final_result == NULL) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    *result_size = count;
    return final_result;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {4, 5, 6, 7, 8};

    Tuple list1 = {arr1, 5};
    Tuple list2 = {arr2, 5};

    int size = 0;
    int *similar = find_similar_elements(list1, list2, &size);

    printf("Similar elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", similar[i]);
    }
    printf("\n");

    free(similar);
    return 0;
}