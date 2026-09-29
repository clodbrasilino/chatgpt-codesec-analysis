#include <stdio.h>
#include <stdlib.h>

int find_extra_element_index(const int *arr1, const int *arr2, int n) {
    int low = 0;
    int high = n - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr1[mid] == arr2[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int n = atoi(argv[1]);
    const char *ptr1_str = argv[2];
    const char *ptr2_str = argv[3];

    if (n <= 0 || ptr1_str == NULL || ptr2_str == NULL) {
        return EXIT_FAILURE;
    }

    int *arr1 = (int *)malloc(n * sizeof(int));
    int *arr2 = (int *)malloc((n - 1) * sizeof(int));

    if (arr1 == NULL || arr2 == NULL) {
        free(arr1);
        free(arr2);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        arr1[i] = atoi(ptr1_str);
        ptr1_str++;
    }

    for (int i = 0; i < n - 1; i++) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        arr2[i] = atoi(ptr2_str);
        ptr2_str++;
    }

    int index = find_extra_element_index(arr1, arr2, n);
    printf("%d\n", index);

    free(arr1);
    free(arr2);

    return EXIT_SUCCESS;
}