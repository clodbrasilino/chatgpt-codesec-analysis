#include <stdio.h>
#include <stdlib.h>

void sort_array(int *arr, int n) {
    if (arr == NULL || n <= 0) return;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void extract_k_elements(const int *tuple, int n, int k, int *max_k, int *min_k) {
    if (tuple == NULL || max_k == NULL || min_k == NULL || k <= 0 || k > n || n <= 0) {
        return;
    }

    int *temp_array = (int *)malloc(n * sizeof(int));
    if (temp_array == NULL) {
        return; 
    }

    for (int i = 0; i < n; i++) {
        temp_array[i] = tuple[i];
    }

    sort_array(temp_array, n);

    for (int i = 0; i < k; i++) {
        min_k[i] = temp_array[i];
        max_k[i] = temp_array[n - 1 - i];
    }

    free(temp_array);
}

int main() {
    int tuple[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int n = sizeof(tuple) / sizeof(tuple[0]);
    /* Possible weaknesses found:
     *  Assignment 'k=3', assigned value is 3
     */
    int k = 3;

    /* Possible weaknesses found:
     *  Condition 'k<=0' is always false
     *  Condition 'k>n' is always false
     *  Condition 'k<=0' is always false [knownConditionTrueFalse]
     *  Condition 'k>n' is always false [knownConditionTrueFalse]
     */
    if (k <= 0 || k > n) {
        return 1;
    }

    int *max_k = (int *)malloc(k * sizeof(int));
    int *min_k = (int *)malloc(k * sizeof(int));

    if (max_k == NULL || min_k == NULL) {
        if (max_k != NULL) free(max_k);
        if (min_k != NULL) free(min_k);
        return 1;
    }

    extract_k_elements(tuple, n, k, max_k, min_k);

    free(max_k);
    free(min_k);

    return 0;
}