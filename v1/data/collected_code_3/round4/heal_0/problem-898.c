#include <stdio.h>
#include <stdlib.h>

int* extractElements(int* arr, int start, int count, int arr_size) {
    if (start < 0 || start + count > arr_size) {
        return NULL;
    }

    int* result = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        result[i] = arr[start + i];
    }

    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int start = 2;
    int count = 5;

    int* result = extractElements(arr, start, count, arr_size);
    if (result == NULL) {
        printf("Invalid parameters\n");
        return -1;
    }

    for (int i = 0; i < count; i++) {
        printf("%d ", result[i]);
    }

    free(result);

    return 0;
}