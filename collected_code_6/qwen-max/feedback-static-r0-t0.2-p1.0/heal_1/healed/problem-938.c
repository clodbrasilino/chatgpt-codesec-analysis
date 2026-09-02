#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void findThreeClosest(int *arr1, int n1, int *arr2, int n2, int *arr3, int n3) {
    int i = 0, j = 0, k = 0;
    int min_diff = INT_MAX;
    int res_i, res_j, res_k;

    while (i < n1 && j < n2 && k < n3) {
        if (arr1[i] > arr2[j]) {
            if (arr1[i] > arr3[k]) {
                if (arr3[k] > arr2[j]) {
                    goto update_min_val;
                }
            } else {
                goto update_max_val;
            }
        } else {
            if (arr2[j] > arr3[k]) {
                if (arr1[i] > arr3[k]) {
                    goto update_min_val;
                }
            } else {
                goto update_max_val;
            }
        }

update_max_val:
        int max_val = (arr1[i] > arr2[j]) ? ((arr1[i] > arr3[k]) ? arr1[i] : arr3[k]) : ((arr2[j] > arr3[k]) ? arr2[j] : arr3[k]);
        int min_val = (arr1[i] < arr2[j]) ? ((arr1[i] < arr3[k]) ? arr1[i] : arr3[k]) : ((arr2[j] < arr3[k]) ? arr2[j] : arr3[k]);

        if (max_val - min_val < min_diff) {
            min_diff = max_val - min_val;
            res_i = i;
            res_j = j;
            res_k = k;
        }

update_min_val:
        if (arr1[i] == min_val) i++;
        else if (arr2[j] == min_val) j++;
        else k++;
    }

    if (min_diff != INT_MAX) {
        printf("The three closest elements are: %d, %d, %d\n", arr1[res_i], arr2[res_j], arr3[res_k]);
    }
}

int main() {
    int arr1[] = {1, 4, 10};
    int arr2[] = {2, 15, 20};
    int arr3[] = {10, 12};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    findThreeClosest(arr1, n1, arr2, n2, arr3, n3);

    return 0;
}