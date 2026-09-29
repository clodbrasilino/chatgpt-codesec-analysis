#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <errno.h>

double tuple_to_float(int integer_part, int fractional_part) {
    if (fractional_part < 0) {
        return -1.0; 
    }

    double fraction = (double)fractional_part;
    while (fraction >= 1.0) {
        fraction /= 10.0;
    }

    double result = (double)integer_part;
    if (integer_part < 0) {
        result -= fraction;
    } else {
        result += fraction;
    }

    return result;
}

int main(int argc, const char *argv[]) {
    int int_part = 42;
    int frac_part = 567;

    if (argc >= 3) {
        char *endptr;
        long val;

        errno = 0;
        val = strtol(argv[1], &endptr, 10);
        if (errno == ERANGE || val < INT_MIN || val > INT_MAX || endptr == argv[1] || *endptr != '\0') {
            printf("Invalid input\n");
            return 1;
        }
        int_part = (int)val;

        errno = 0;
        val = strtol(argv[2], &endptr, 10);
        if (errno == ERANGE || val < INT_MIN || val > INT_MAX || endptr == argv[2] || *endptr != '\0') {
            printf("Invalid input\n");
            return 1;
        }
        frac_part = (int)val;
    }

    double result = tuple_to_float(int_part, frac_part);
    
    if (result != -1.0 || (int_part == -1 && frac_part == 0)) {
        printf("%f\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}