#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

void findClosestElements(const int arr1[], const int arr2[], const int arr3[], int n1, int n2, int n3) {
    if (n1 <= 0 || n2 <= 0 || n3 <= 0) {
        return;
    }

    int i = 0, j = 0, k = 0;
    int min_diff = INT_MAX;
    int res_i = 0, res_j = 0, res_k = 0;

    while (i < n1 && j < n2 && k < n3) {
        int min_val = arr1[i];
        if (arr2[j] < min_val) min_val = arr2[j];
        if (arr3[k] < min_val) min_val = arr3[k];

        int max_val = arr1[i];
        if (arr2[j] > max_val) max_val = arr2[j];
        if (arr3[k] > max_val) max_val = arr3[k];

        int diff = max_val - min_val;

        if (diff < min_diff) {
            min_diff = diff;
            res_i = arr1[i];
            res_j = arr2[j];
            res_k = arr3[k];
        }

        if (min_diff == 0) {
            break;
        }

        if (arr1[i] == min_val) {
            i++;
        } else if (arr2[j] == min_val) {
            j++;
        } else {
            k++;
        }
    }

    printf("%d %d %d\n", res_i, res_j, res_k);
}

int main(void) {
    int arr1[] = {1, 4, 10, 20, 40, 80};
    int arr2[] = {6, 7, 20, 80, 100};
    int arr3[] = {3, 4, 15, 20, 30, 70, 80, 120};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    findClosestElements(arr1, arr2, arr3, n1, n2, n3);

    return 0;
}