#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int find_insertion_point(int *array, size_t size, int value) {
    if (array == NULL) {
        return 0;
    }

    size_t low = 0;
    size_t high = size;

    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (array[mid] <= value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return (int)low;
}

int main(void) {
    int arr1[] = {1, 3, 5, 7, 9};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);

    int val1 = 6;
    int point1 = find_insertion_point(arr1, size1, val1);
    printf("Insertion point for %d: %d\n", val1, point1);

    int val2 = 10;
    int point2 = find_insertion_point(arr1, size1, val2);
    printf("Insertion point for %d: %d\n", val2, point2);

    int val3 = 0;
    int point3 = find_insertion_point(arr1, size1, val3);
    printf("Insertion point for %d: %d\n", val3, point3);

    int val4 = 5;
    int point4 = find_insertion_point(arr1, size1, val4);
    printf("Insertion point for %d: %d\n", val4, point4);

    int *arr2 = NULL;
    size_t size2 = 0;
    int val5 = 5;
    int point5 = find_insertion_point(arr2, size2, val5);
    printf("Insertion point for %d in NULL array: %d\n", val5, point5);

    return EXIT_SUCCESS;
}