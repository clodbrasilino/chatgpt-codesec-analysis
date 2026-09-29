#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void find_three_closest(const int arr1[], int n1, const int arr2[], int n2, const int arr3[], int n3, int result[3]) {
    int i = 0, j = 0, k = 0;
    int min_diff = INT_MAX;

    while (i < n1 && j < n2 && k < n3) {
        int current_max = arr1[i];
        if (arr2[j] > current_max) current_max = arr2[j];
        if (arr3[k] > current_max) current_max = arr3[k];

        int current_min = arr1[i];
        if (arr2[j] < current_min) current_min = arr2[j];
        if (arr3[k] < current_min) current_min = arr3[k];

        int diff = current_max - current_min;

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

int main() {
    const int arr1[] = {1, 4, 10};
    const int arr2[] = {2, 15, 20};
    const int arr3[] = {10, 12};
    /* Possible weaknesses found:
     *  Assignment 'n1=sizeof(arr1)/sizeof(arr1[0])', assigned value is 3
     */
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    /* Possible weaknesses found:
     *  Assignment 'n2=sizeof(arr2)/sizeof(arr2[0])', assigned value is 3
     */
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    /* Possible weaknesses found:
     *  Assignment 'n3=sizeof(arr3)/sizeof(arr3[0])', assigned value is 2
     */
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    /* Possible weaknesses found:
     *  Condition 'n2>0' is always true [knownConditionTrueFalse]
     *  Condition 'n3>0' is always true
     *  Condition 'n3>0' is always true [knownConditionTrueFalse]
     *  Condition 'n1>0' is always true [knownConditionTrueFalse]
     *  Condition 'n2>0' is always true
     *  Condition 'n1>0' is always true
     */
    if (n1 > 0 && n2 > 0 && n3 > 0) {
        int result[3];
        find_three_closest(arr1, n1, arr2, n2, arr3, n3, result);
        printf("%d %d %d\n", result[0], result[1], result[2]);
        return EXIT_SUCCESS;
    } 
    
    return EXIT_FAILURE;
}