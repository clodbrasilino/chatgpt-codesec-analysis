#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr3' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr2' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr1' can be declared as pointer to const [constParameterPointer]
 */
void findClosestTriplet(int *arr1, int n1, int *arr2, int n2, int *arr3, int n3, int *res1, int *res2, int *res3) {
    int i = 0, j = 0, k = 0;
    int min_diff = INT_MAX;

    while (i < n1 && j < n2 && k < n3) {
        int minimum = arr1[i];
        if (arr2[j] < minimum) minimum = arr2[j];
        if (arr3[k] < minimum) minimum = arr3[k];

        int maximum = arr1[i];
        if (arr2[j] > maximum) maximum = arr2[j];
        if (arr3[k] > maximum) maximum = arr3[k];

        int diff = maximum - minimum;

        if (diff < min_diff) {
            min_diff = diff;
            *res1 = arr1[i];
            *res2 = arr2[j];
            *res3 = arr3[k];
        }

        if (min_diff == 0) break;

        if (arr1[i] == minimum) i++;
        else if (arr2[j] == minimum) j++;
        else k++;
    }
}

int main(void) {
    int arr1[] = {1, 4, 10};
    int arr2[] = {2, 15, 20};
    int arr3[] = {10, 12};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    int res1, res2, res3;

    findClosestTriplet(arr1, n1, arr2, n2, arr3, n3, &res1, &res2, &res3);

    printf("%d %d %d\n", res1, res2, res3);

    return 0;
}