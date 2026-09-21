#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

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

long strtol_safe(const char *str, char **endptr) {
    errno = 0;
    long val = strtol(str, endptr, 10);
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return LONG_MIN;
    }
    return val;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long n_long = strtol_safe(argv[1], &endptr);
    if (n_long == LONG_MIN || *endptr != '\0' || n_long <= 0) {
        return EXIT_FAILURE;
    }
    int n = (int)n_long;

    const char *ptr1_str = argv[2];
    const char *ptr2_str = argv[3];

    if (ptr1_str == NULL || ptr2_str == NULL) {
        return EXIT_FAILURE;
    }

    int *arr1 = (int *)malloc(n * sizeof(int));
    int *arr2 = (int *)malloc((n - 1) * sizeof(int));

    if (arr1 == NULL || arr2 == NULL) {
        free(arr1);
        free(arr2);
        return EXIT_FAILURE;
    }

    char *endptr1;
    for (int i = 0; i < n; i++) {
        long val = strtol_safe(ptr1_str, &endptr1);
        if (val == LONG_MIN) {
            free(arr1); free(arr2); return EXIT_FAILURE;
        }
        arr1[i] = (int)val;
        ptr1_str = endptr1;
        if (*ptr1_str == ',') ptr1_str++;
    }

    char *endptr2;
    for (int i = 0; i < n - 1; i++) {
        long val = strtol_safe(ptr2_str, &endptr2);
        if (val == LONG_MIN) {
            free(arr1); free(arr2); return EXIT_FAILURE;
        }
        arr2[i] = (int)val;
        ptr2_str = endptr2;
        if (*ptr2_str == ',') ptr2_str++;
    }

    int index = find_extra_element_index(arr1, arr2, n);
    printf("%d\n", index);

    free(arr1);
    free(arr2);

    return EXIT_SUCCESS;
}