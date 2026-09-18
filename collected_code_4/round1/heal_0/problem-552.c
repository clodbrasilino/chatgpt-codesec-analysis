#include <stdbool.h>
#include <float.h>
#include <stdio.h>

bool checkIsLinear(float* arr, int numElements) {
    if(numElements <= 1){
        return true;
    }

    float ratio = arr[1] - arr[0];
    for(int idx = 2; idx < numElements; ++idx) {
        if(arr[idx] - arr[idx-1] != ratio) {
            return false;
        }
    }

    return true;
}

int main() {
    float array1[] = {1, 3, 5, 7};
    float array2[] = {1, 2, 4, 8};

    if (checkIsLinear(array1, sizeof(array1) / sizeof(array1[0]))) {
        printf("Array1 is linear.\n");
    } else {
        printf("Array1 is not linear.\n");
    }

    if (checkIsLinear(array2, sizeof(array2) / sizeof(array2[0]))) {
        printf("Array2 is linear.\n");
    } else {
        printf("Array2 is not linear.\n");
    }

    return 0;
}