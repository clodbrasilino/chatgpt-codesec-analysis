#include <stdio.h>
#include <stdlib.h>

int min_operations(int a, int b) {
    if (a < 0 || b < 0) {
        return -1;
    }
    if (a == b) {
        return 0;
    }
    if (a < b) {
        int temp = a;
        a = b;
        b = temp;
    }
    int operations = 0;
    while (a > b) {
        if ((a / 2) >= b && a % 2 == 0) {
            a /= 2;
        } else {
            a -= 1;
        }
        operations++;
    }
    operations += (b - a);
    return operations;
}

int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || val1 < 0) {
        fprintf(stderr, "Invalid input for num1\n");
        return EXIT_FAILURE;
    }
    char *endptr2;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || val2 < 0) {
        fprintf(stderr, "Invalid input for num2\n");
        return EXIT_FAILURE;
    }
    int result = min_operations((int)val1, (int)val2);
    if (result == -1) {
        fprintf(stderr, "Invalid parameters\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", result);
    return EXIT_SUCCESS;
}