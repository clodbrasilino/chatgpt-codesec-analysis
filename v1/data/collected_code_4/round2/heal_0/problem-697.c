#include <stdio.h>

size_t countEven(const int* array, size_t arrayLength) {
    if(array == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < arrayLength; i++) {
        if (array[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[]={1,2,3,4,5,6,7,8,9,10};
    size_t count = countEven(arr, sizeof(arr)/sizeof(int));

    printf("Number of even elements: %zu\n", count);

    return 0;
}