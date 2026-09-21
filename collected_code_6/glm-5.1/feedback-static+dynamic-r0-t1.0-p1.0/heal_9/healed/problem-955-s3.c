#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_abundant(int num) {
    if (num <= 1) {
        return 0;
    }
    int sum = 1;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }
    return sum > num;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 2 || val > INT_MAX) {
        printf("Invalid input. Please provide an integer between 2 and %d.\n", INT_MAX);
        return 1;
    }
    int number = (int)val;
    if (is_abundant(number)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}