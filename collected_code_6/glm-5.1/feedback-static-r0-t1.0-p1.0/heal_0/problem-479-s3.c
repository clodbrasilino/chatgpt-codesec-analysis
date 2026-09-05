#include <stdio.h>
#include <stdlib.h>

int find_first_digit(int number) {
    if (number == 0) {
        return 0;
    }
    int n = abs(number);
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int number = (int)val;
    int first_digit = find_first_digit(number);
    printf("%d\n", first_digit);
    return EXIT_SUCCESS;
}