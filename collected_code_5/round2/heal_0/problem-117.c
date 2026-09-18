#include <stdio.h>
#include <stdlib.h>

void convertToFloat(float *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = (float)arr[i];
    }
}

int main() {
    int size = 5;
    float *arr = malloc(sizeof(float) * size);

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }

    convertToFloat(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%f\n", arr[i]);
    }
    
    free(arr);

    return 0;
}