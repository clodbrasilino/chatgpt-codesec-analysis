#include <stdio.h>
#include <stdlib.h>

long long sum_of_ap(long long first_term, long long common_diff, long long num_terms) {
    if (num_terms <= 0) {
        return 0;
    }
    long long last_term = first_term + (num_terms - 1) * common_diff;
    if (common_diff == 0) {
        return first_term * num_terms;
    }
    long long total = num_terms * (first_term + last_term);
    return total / 2;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_diff> <num_terms>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1, *endptr2, *endptr3;
    long long first_term = strtoll(argv[1], &endptr1, 10);
    long long common_diff = strtoll(argv[2], &endptr2, 10);
    long long num_terms = strtoll(argv[3], &endptr3, 10);
    if (*endptr1 != '\0' || *endptr2 != '\0' || *endptr3 != '\0') {
        fprintf(stderr, "Invalid input: arguments must be integers\n");
        return EXIT_FAILURE;
    }
    if (num_terms < 0) {
        fprintf(stderr, "Invalid input: num_terms cannot be negative\n");
        return EXIT_FAILURE;
    }
    long long result = sum_of_ap(first_term, common_diff, num_terms);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}