#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool can_be_sorted_by_corners(const int *arr, int n) {
    if (n <= 2) {
        return true;
    }

    bool mismatch = false;
    const int *end = arr + n;
    for (const int *it = arr; it != end - 1; ++it) {
        if (*it != *(it + 1)) {
            mismatch = true;
            break;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder mismatch: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    if (!mismatch) {
        return true;
    }

    bool inc = arr[1] > arr[0];
    for (const int *it = arr + 2; it != end; ++it) {
        bool curr_inc = *it > *(it - 1);
        if (curr_inc != inc) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }
    if (n == 0) {
        printf("true\n");
        return 0;
    }
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }
    bool result = can_be_sorted_by_corners(arr, n);
    printf("%s\n", result ? "true" : "false");
    free(arr);
    return 0;
}