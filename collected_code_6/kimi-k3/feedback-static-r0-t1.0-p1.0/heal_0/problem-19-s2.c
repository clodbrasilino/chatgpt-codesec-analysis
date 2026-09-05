#include <stdio.h>
#include <stdlib.h>

int compare_integers(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int contains_duplicate(const int *arr, size_t size)
{
    if (arr == NULL || size == 0) {
        return 0;
    }
    
    int *temp = malloc(size * sizeof(int));
    if (temp == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    
    qsort(temp, size, sizeof(int), compare_integers);
    
    int result = 0;
    for (size_t i = 1; i < size; i++) {
        if (temp[i] == temp[i - 1]) {
            result = 1;
            break;
        }
    }
    
    free(temp);
    return result;
}

int main(void)
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 2, 5};
    int arr3[] = {5};
    
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    
    int result1 = contains_duplicate(arr1, size1);
    int result2 = contains_duplicate(arr2, size2);
    int result3 = contains_duplicate(arr3, size3);
    
    if (result1 >= 0) {
        printf("Array 1: %s\n", result1 ? "Contains duplicates" : "No duplicates");
    } else {
        printf("Array 1: Memory allocation failed\n");
    }
    
    if (result2 >= 0) {
        printf("Array 2: %s\n", result2 ? "Contains duplicates" : "No duplicates");
    } else {
        printf("Array 2: Memory allocation failed\n");
    }
    
    if (result3 >= 0) {
        printf("Array 3: %s\n", result3 ? "Contains duplicates" : "No duplicates");
    } else {
        printf("Array 3: Memory allocation failed\n");
    }
    
    return 0;
}