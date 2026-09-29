#include <stdbool.h>
#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
bool isMonotonic(int *array, int size) {
    if (size <= 1) return true;

    bool increasing = array[1] >= array[0];
    bool decreasing = array[1] <= array[0];

    for (int i = 2; i < size; ++i) {
        if (decreasing && array[i] > array[i - 1]) return false;
        if (increasing && array[i] < array[i - 1]) return false;
    }

    return true;
}

int main() {
    int arr1[] = {1, 2, 4, 20};
    int arr2[] = {1, 20, 4, 10};
    int arr3[] = {4, 1, 0, -10};

    printf("%s\n", isMonotonic(arr1, sizeof(arr1) / sizeof(arr1[0])) ? "True" : "False");
    printf("%s\n", isMonotonic(arr2, sizeof(arr2) / sizeof(arr2[0])) ? "True" : "False");
    printf("%s\n", isMonotonic(arr3, sizeof(arr3) / sizeof(arr3[0])) ? "True" : "False");

    return 0;
}