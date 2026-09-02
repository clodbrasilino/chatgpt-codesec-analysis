#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int a, b, c;
} Triple;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/* Possible weaknesses found:
 *  Parameter 'arr1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr3' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr2' can be declared as pointer to const [constParameterPointer]
 */
Triple findClosest(int *arr1, int size1, int *arr2, int size2, int *arr3, int size3) {
    int i = 0, j = 0, k = 0;
    int min_diff = INT_MAX;
    Triple closest = {0, 0, 0};

    while (i < size1 && j < size2 && k < size3) {
        int current_diff = abs(arr1[i] - arr2[j]) + abs(arr1[i] - arr3[k]) + abs(arr2[j] - arr3[k]);
        if (current_diff < min_diff) {
            min_diff = current_diff;
            closest.a = arr1[i];
            closest.b = arr2[j];
            closest.c = arr3[k];
        }

        if (arr1[i] <= arr2[j] && arr1[i] <= arr3[k])
            i++;
        else if (arr2[j] <= arr1[i] && arr2[j] <= arr3[k])
            j++;
        else
            k++;
    }
    return closest;
}

int main() {
    int arr1[] = {1, 4, 10};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {2, 15, 20};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    int arr3[] = {10, 12};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    Triple closest = findClosest(arr1, size1, arr2, size2, arr3, size3);

    printf("The closest elements are %d, %d, %d\n", closest.a, closest.b, closest.c);

    return 0;
}