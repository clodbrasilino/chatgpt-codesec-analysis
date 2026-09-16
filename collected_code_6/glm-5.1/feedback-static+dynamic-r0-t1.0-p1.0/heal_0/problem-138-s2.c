#include <stdio.h>
#include <stdlib.h>

int can_be_sum_of_nonzero_powers_of_2(long long n) {
    if (n <= 1) {
        return 0;
    }
    long long count = 0;
    long long temp = n;
    while (temp > 0) {
        temp &= (temp - 1);
        count++;
        if (count >= 2) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    long long num;
    if (argc != 2) {
        if (fscanf(stdin, "%lld", &num) != 1) {
            return EXIT_FAILURE;
        }
    } else {
        char *endptr;
        num = strtoll(argv[1], &endptr, 10);
        if (*endptr != '\0' || errno == ERANGE) {
            return EXIT_FAILURE;
        }
    }
    if (can_be_sum_of_nonzero_powers_of_2(num)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return EXIT_SUCCESS;
}