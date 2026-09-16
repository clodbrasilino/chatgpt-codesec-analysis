#include <stdio.h>
#include <stdlib.h>

long long productOfNonRepeated(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 1;
    }

    long long product = 1;
    int hasNonRepeated = 0;

    for (size_t i = 0; i < size; ++i) {
        int isRepeated = 0;
        for (size_t j = 0; j < size; ++j) {
            if (i != j && arr[i] == arr[j]) {
                isRepeated = 1;
                break;
            }
        }
        if (!isRepeated) {
            product *= arr[i];
            hasNonRepeated = 1;
        }
    }

    return hasNonRepeated ? product : 1;
}

int main(void) {
    int arr[] = {2, 3, 4, 5, 2, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    long long result = productOfNonRepeated(arr, size);
    printf("%lld\n", result);

    return 0;
}