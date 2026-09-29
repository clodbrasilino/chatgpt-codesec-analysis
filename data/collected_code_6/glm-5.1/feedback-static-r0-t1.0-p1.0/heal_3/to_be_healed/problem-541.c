#include <stdio.h>
#include <stdlib.h>

int is_abundant(int num) {
    if (num <= 0) {
        return 0;
    }

    int sum = 1;

    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }

    return sum > num;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val < 1 || val > 2147483647) {
        fprintf(stderr, "Error: Invalid input. Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }

    num = (int)val;

    if (is_abundant(num)) {
        printf("%d is an abundant number.\n", num);
    } else {
        printf("%d is not an abundant number.\n", num);
    }

    return EXIT_SUCCESS;
}