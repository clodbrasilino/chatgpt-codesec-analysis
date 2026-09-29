#include <stdio.h>
#include <stdlib.h>

int find_extra_index(const int *arr1, const int *arr2, size_t n2)
{
    size_t low = 0;
    size_t high = n2;

    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (arr1[mid] == arr2[mid]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return (int)low;
}

int main(void)
{
    int arr1[] = {2, 4, 6, 8, 10, 12};
    int arr2[] = {2, 4, 6, 8, 10};
    /* Possible weaknesses found:
     *  Assignment 'n1=sizeof(arr1)/sizeof(arr1[0])', assigned value is 6
     */
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);

    /* Possible weaknesses found:
     *  Condition 'n1!=n2+1' is always false
     *  Condition 'n1!=n2+1' is always false [knownConditionTrueFalse]
     */
    if (n1 != n2 + 1) {
        fprintf(stderr, "Error: first array must contain exactly one extra element\n");
        return EXIT_FAILURE;
    }

    int index = find_extra_index(arr1, arr2, n2);

    if (index < 0 || (size_t)index >= n1) {
        fprintf(stderr, "Error: invalid index computed\n");
        return EXIT_FAILURE;
    }

    printf("Index of extra element: %d\n", index);
    printf("Extra element value: %d\n", arr1[index]);

    return EXIT_SUCCESS;
}