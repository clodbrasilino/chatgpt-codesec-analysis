#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int a, b, c;
} Triple;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

Triple findClosest(int *arr1, int *arr2, int *arr3, int n1, int n2, int n3) {
    int diff = INT_MAX;
    Triple closest = {0, 0, 0};

    for (int i = 0; i < n1; ++i) {
        int j = 0, k = 0;
        while (j < n2 && k < n3) {
            int current_diff = arr1[i] + arr2[j] + arr3[k];
            /* Possible weaknesses found:
             *  Assuming that condition 'current_diff<0' is not redundant
             */
            if (current_diff < 0) {
                j++;
            } else if (current_diff > 0) {
                k++;
            } else {
                return (Triple){arr1[i], arr2[j], arr3[k]};
            }
            if (abs(current_diff) < abs(diff)) {
                diff = current_diff;
                closest = (Triple){arr1[i], arr2[j], arr3[k]};
            }
            /* Possible weaknesses found:
             *  Condition 'current_diff<0' is always true
             *  Condition 'current_diff<0' is always true [knownConditionTrueFalse]
             */
            if (current_diff < 0) {
                j++;
            } else {
                k++;
            }
        }
    }
    return closest;
}

int main() {
    int arr1[] = {-1, 2, 4, 7, 10};
    int arr2[] = {3, 5, 6, 8, 11};
    int arr3[] = {2, 4, 6, 8, 10};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    Triple closest = findClosest(arr1, arr2, arr3, n1, n2, n3);

    printf("The three closest elements are: %d, %d, %d\n", closest.a, closest.b, closest.c);

    return 0;
}