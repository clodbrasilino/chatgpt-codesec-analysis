#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int add_with_range(int a, int b, int min_range, int max_range, int *result) {
    int sum;

    if (result == NULL) {
        return -1;
    }

    if ((b > 0) && (a > INT_MAX - b)) {
        return -1;
    }
    if ((b < 0) && (a < INT_MIN - b)) {
        return -1;
    }

    sum = a + b;

    if (sum >= min_range && sum <= max_range) {
        *result = 20;
    } else {
        *result = sum;
    }

    return 0;
}

int main(void) {
    int result = 0;
    int status = 0;

    status = add_with_range(5, 4, 10, 20, &result);
    if (status == 0) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Error during calculation.\n");
        return EXIT_FAILURE;
    }

    status = add_with_range(8, 7, 10, 20, &result);
    if (status == 0) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Error during calculation.\n");
        return EXIT_FAILURE;
    }

    status = add_with_range(15, 10, 10, 20, &result);
    if (status == 0) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Error during calculation.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}