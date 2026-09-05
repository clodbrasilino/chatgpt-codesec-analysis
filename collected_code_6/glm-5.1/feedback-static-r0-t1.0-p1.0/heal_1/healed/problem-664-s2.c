#include <stdio.h>
#include <stdlib.h>

int average_of_even_till(int target) {
    if (target <= 0 || target % 2 != 0) {
        return -1;
    }

    long long count = target / 2;
    if (count == 0) {
        return -1;
    }

    long long sum = count * (count + 1);
    long long avg = sum / count;

    if (avg > 2147483647 || avg < -2147483648) {
        return -1;
    }

    return (int)avg;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > 2147483647 || val < -2147483648) {
        return EXIT_FAILURE;
    }

    int target = (int)val;
    int result = average_of_even_till(target);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}