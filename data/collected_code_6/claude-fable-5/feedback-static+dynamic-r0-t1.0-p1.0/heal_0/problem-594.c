#include <stdio.h>
#include <stdlib.h>

int diff_first_even_odd(const int *arr, size_t n, int *result)
{
    size_t i;
    int first_even = 0;
    int first_odd = 0;
    int found_even = 0;
    int found_odd = 0;

    if (arr == NULL || result == NULL || n == 0U) {
        return -1;
    }

    for (i = 0U; i < n; i++) {
        if (!found_even && (arr[i] % 2) == 0) {
            first_even = arr[i];
            found_even = 1;
        }
        if (!found_odd && (arr[i] % 2) != 0) {
            first_odd = arr[i];
            found_odd = 1;
        }
        if (found_even && found_odd) {
            break;
        }
    }

    if (!found_even || !found_odd) {
        return -1;
    }

    *result = first_even - first_odd;
    return 0;
}

int main(void)
{
    int list1[] = {2, 4, 5, 8, 9};
    int list2[] = {7, 3, 4, 10};
    int list3[] = {2, 4, 6, 8};
    int result = 0;

    if (diff_first_even_odd(list1, sizeof(list1) / sizeof(list1[0]), &result) == 0) {
        printf("Difference: %d\n", result);
    } else {
        fprintf(stderr, "Could not compute difference for list1\n");
    }

    if (diff_first_even_odd(list2, sizeof(list2) / sizeof(list2[0]), &result) == 0) {
        printf("Difference: %d\n", result);
    } else {
        fprintf(stderr, "Could not compute difference for list2\n");
    }

    if (diff_first_even_odd(list3, sizeof(list3) / sizeof(list3[0]), &result) == 0) {
        printf("Difference: %d\n", result);
    } else {
        fprintf(stderr, "Could not compute difference for list3\n");
    }

    return EXIT_SUCCESS;
}