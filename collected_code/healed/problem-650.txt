#include <stdbool.h>

bool areArraysEqual(const int* arr1, int size1, const int* arr2, int size2) {
    if (size1 != size2) {
        return false;
    }
    
    for (int i = 0; i < size1; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(arr1)/sizeof(arr1[0]);
    int size2 = sizeof(arr2)/sizeof(arr2[0]);
    
    bool result = areArraysEqual(arr1, size1, arr2, size2);

    return 0;
}