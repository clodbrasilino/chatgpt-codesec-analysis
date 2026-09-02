#include <stdbool.h>
#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
bool isMonotonic(int *array, int size) {
    if (size <= 1) return true;

    bool increasing = true;
    bool decreasing = true;

    for (int i = 1; i < size; ++i) {
        if (array[i] > array[i - 1]) decreasing = false;
        if (array[i] < array[i - 1]) increasing = false;
    }

    return increasing || decreasing;
}

int main() {
    int array1[] = {1, 2, 4, 20};
    int array2[] = {1, 20, 4, 10};
    int array3[] = {4, 1, 0, -10};

    int size1 = sizeof(array1) / sizeof(array1[0]);
    int size2 = sizeof(array2) / sizeof(array2[0]);
    int size3 = sizeof(array3) / sizeof(array3[0]);

    printf("Array 1 is %s\n", isMonotonic(array1, size1) ? "monotonic" : "not monotonic");
    printf("Array 2 is %s\n", isMonotonic(array2, size2) ? "monotonic" : "not monotonic");
    printf("Array 3 is %s\n", isMonotonic(array3, size3) ? "monotonic" : "not monotonic");

    return 0;
}