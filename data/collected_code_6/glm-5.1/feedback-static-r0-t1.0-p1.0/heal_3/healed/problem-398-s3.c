#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int compute_sum_of_digits(int num) {
    int sum = 0;
    int n = abs(num);
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main(int argc, char const * const argv[]) {
    if (argc < 2) {
        return 1;
    }

    size_t count = (size_t)(argc - 1);
    int *numbers = malloc(count * sizeof(int));
    if (numbers == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; ++i) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (errno == ERANGE || endptr == argv[i + 1] || *endptr != '\0') {
            numbers[i] = 0;
        } else if (val > INT_MAX) {
            numbers[i] = INT_MAX;
        } else if (val < INT_MIN) {
            numbers[i] = INT_MIN;
        } else {
            numbers[i] = (int)val;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        int sum = compute_sum_of_digits(numbers[i]);
        printf("%d\n", sum);
    }

    free(numbers);
    numbers = NULL;

    return 0;
}