#include <stdio.h>
#include <stdlib.h>

int sum_of_divisors(int num) {
    if (num <= 0) {
        return 0;
    }
    int sum = 1;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i * i != num) {
                sum += num / i;
            }
        }
    }
    return sum;
}

int check_divisor_sum_equal(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }
    return sum_of_divisors(a) == sum_of_divisors(b);
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || val1 <= 0 || val1 > 2147483647) {
        fprintf(stderr, "Invalid input for num1\n");
        return EXIT_FAILURE;
    }
    char *endptr2;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || val2 <= 0 || val2 > 2147483647) {
        fprintf(stderr, "Invalid input for num2\n");
        return EXIT_FAILURE;
    }
    int result = check_divisor_sum_equal((int)val1, (int)val2);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}