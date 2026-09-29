#include <stdio.h>
#include <stdlib.h>

int* extractElements(int* arr, int start, int count) {
    int* result = (int*)malloc(sizeof(int) * count);
    if(result == NULL) {
        return NULL;
    }
    for(int i = 0; i < count; i++) {
        result[i] = arr[start + i];
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int start = 2;
    int count = 5;
    int* extracted = extractElements(arr, start, count);

    if(extracted == NULL) {
        return 1;
    }

    for(int i = 0; i < count; i++) {
        printf("%d ", extracted[i]);
    }
    free(extracted);
    return 0;
}