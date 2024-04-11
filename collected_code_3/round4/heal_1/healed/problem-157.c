#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} RunLength;

RunLength* runLengthEncode(int* arr, int size, int* outputSize) {
    if (size <= 0 || !arr || !outputSize) return NULL;
    
    RunLength* output = (RunLength*)malloc(sizeof(RunLength) * size);
    
    if (output == NULL) return NULL;
    
    int outputIndex = 0;

    for (int i = 0; i < size; i++) {
        int count = 1;
        while (i + 1 < size && arr[i] == arr[i + 1]) {
            i++;
            count++;
        }

        output[outputIndex].value = arr[i];
        output[outputIndex].count = count;
        outputIndex++;
    }

    *outputSize = outputIndex;
    return output;
}

void printRunLength(RunLength* arr, int size) {
    if (size <= 0 || !arr) return;

    for (int i = 0; i < size; i++) {
        printf("%d:%d ", arr[i].value, arr[i].count);
    }
    
    printf("\n");
}

int main() {
    int arr[] = {1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    int outputSize;
    RunLength* encoded = runLengthEncode(arr, size, &outputSize);

    if (encoded == NULL) {
        return 1;  // Error handling
    }

    printRunLength(encoded, outputSize);

    free(encoded);

    return 0;
}