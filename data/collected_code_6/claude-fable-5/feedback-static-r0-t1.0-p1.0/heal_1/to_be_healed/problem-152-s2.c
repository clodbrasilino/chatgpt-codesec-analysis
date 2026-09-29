#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int merge(int *arr, size_t left, size_t mid, size_t right)
{
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;
    size_t i, j, k;
    int *L;
    int *R;

    L = malloc(n1 * sizeof(int));
    if (L == NULL) {
        return -1;
    }

    R = malloc(n2 * sizeof(int));
    if (R == NULL) {
        free(L);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(L, &arr[left], n1 * sizeof(int));
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(R, &arr[mid + 1], n2 * sizeof(int));

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
    return 0;
}

static int merge_sort(int *arr, size_t left, size_t right)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'mid' can be reduced. [variableScope]
     */
    size_t mid;

    if (arr == NULL) {
        return -1;
    }

    if (left < right) {
        mid = left + (right - left) / 2;
        if (merge_sort(arr, left, mid) != 0) {
            return -1;
        }
        if (merge_sort(arr, mid + 1, right) != 0) {
            return -1;
        }
        if (merge(arr, left, mid, right) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    int arr[] = { 38, 27, 43, 3, 9, 82, 10 };
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr)/sizeof(arr[0])', assigned value is 7
     */
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t i;

    /* Possible weaknesses found:
     *  Condition 'n>0' is always true
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     */
    if (n > 0) {
        if (merge_sort(arr, 0, n - 1) != 0) {
            fprintf(stderr, "Sorting failed due to memory allocation error\n");
            return EXIT_FAILURE;
        }
    }

    printf("Sorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}