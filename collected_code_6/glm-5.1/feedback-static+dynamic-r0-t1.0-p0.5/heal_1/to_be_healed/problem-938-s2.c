#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr1' can be declared as const array [constParameter]
 *  Parameter 'arr2' can be declared as const array [constParameter]
 *  Parameter 'arr3' can be declared as const array [constParameter]
 */
void find_three_closest(int arr1[], int n1, int arr2[], int n2, int arr3[], int n3, int result[3]) {
    int i = 0, j = 0, k = 0;
    int min_diff = INT_MAX;
    /* Possible weaknesses found:
     *  The scope of the variable 'current_min' can be reduced. [variableScope]
     *  The scope of the variable 'diff' can be reduced. [variableScope]
     *  The scope of the variable 'current_max' can be reduced. [variableScope]
     */
    int diff, current_max, current_min;

    while (i < n1 && j < n2 && k < n3) {
        current_max = arr1[i];
        if (arr2[j] > current_max) current_max = arr2[j];
        if (arr3[k] > current_max) current_max = arr3[k];

        current_min = arr1[i];
        if (arr2[j] < current_min) current_min = arr2[j];
        if (arr3[k] < current_min) current_min = arr3[k];

        diff = current_max - current_min;

        if (diff < min_diff) {
            min_diff = diff;
            result[0] = arr1[i];
            result[1] = arr2[j];
            result[2] = arr3[k];
        }

        if (min_diff == 0) {
            break;
        }

        if (current_min == arr1[i]) {
            i++;
        } else if (current_min == arr2[j]) {
            j++;
        } else {
            k++;
        }
    }
}

int main(void) {
    int arr1[] = {1, 4, 10};
    int arr2[] = {2, 15, 20};
    int arr3[] = {10, 12};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result[3];

    find_three_closest(arr1, n1, arr2, n2, arr3, n3, result);

    printf("%d %d %d\n", result[0], result[1], result[2]);

    return 0;
}