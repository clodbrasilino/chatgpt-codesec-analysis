#include <stdio.h>
#include <stdlib.h>

int count_digits(long long n) {
    if (n == 0) {
        return 1;
    }
    if (n < 0) {
        n = -n;
    }
    int count = 0;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

int same_digits(long long a, long long b) {
    return count_digits(a) == count_digits(b);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    long long num1, num2;
    if (argc == 3) {
        char *endptr1, *endptr2;
        num1 = strtoll(argv[1], &endptr1, 10);
        num2 = strtoll(argv[2], &endptr2, 10);
        if (*endptr1 != '\0' || *endptr2 != '\0') {
            return EXIT_FAILURE;
        }
    } else if (scanf("%lld %lld", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }
    
    if (same_digits(num1, num2)) {
        printf("Same number of digits\n");
    } else {
        printf("Different number of digits\n");
    }
    
    return EXIT_SUCCESS;
}