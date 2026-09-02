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
 *  Parameter 'arr2' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr3' can be declared as pointer to const [constParameterPointer]
 */
Triple findClosest(int *arr1, int *arr2, int *arr3, int n1, int n2, int n3) {
    int diff = INT_MAX;
    Triple result;
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; i < n1; ++i) {
        int j = 0, k = 0;
        while (j < n2 && k < n3) {
            int min_diff = abs(arr1[i] - arr2[j]) + abs(arr2[j] - arr3[k]) + abs(arr3[k] - arr1[i]);
            if (min_diff < diff) {
                diff = min_diff;
                result.a = arr1[i];
                result.b = arr2[j];
                result.c = arr3[k];
            }
            if (arr2[j] < arr3[k]) {
                j++;
            } else {
                k++;
            }
        }
    }
    /* Possible weaknesses found:
     *  Uninitialized variables: result.a, result.b, result.c
     *  Uninitialized variables: result.a, result.b, result.c [uninitvar]
     */
    return result;
}

int main() {
    int arr1[] = {1, 4, 10};
    int arr2[] = {2, 15, 20};
    int arr3[] = {10, 12};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    Triple closest = findClosest(arr1, arr2, arr3, n1, n2, n3);

    printf("The closest elements are: %d, %d, %d\n", closest.a, closest.b, closest.c);

    return 0;
}