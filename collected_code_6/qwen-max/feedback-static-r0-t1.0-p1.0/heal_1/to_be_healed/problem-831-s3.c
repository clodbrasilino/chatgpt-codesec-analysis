#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int countEqualPairs(int *arr, int arrSize) {
    int count = 0;
    for (int i = 0; i < arrSize - 1; ++i) {
        for (int j = i + 1; j < arrSize; ++j) {
            if (arr[i] == arr[j]) {
                ++count;
            }
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 3, 4};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    int result = countEqualPairs(arr, arrSize);
    printf("Number of equal element pairs: %d\n", result);
    return 0;
}