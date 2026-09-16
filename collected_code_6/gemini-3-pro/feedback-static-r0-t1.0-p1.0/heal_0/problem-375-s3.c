#include <stdio.h>
#include <stdlib.h>

int round_to_nearest_multiple(int number, int multiple) {
    if (multiple == 0) {
        return number;
    }

    int remainder = number % multiple;

    if (remainder == 0) {
        return number;
    }

    int half_multiple = multiple / 2;

    if (number > 0) {
        if (multiple > 0) {
            if (remainder >= half_multiple + (multiple % 2)) {
                return number + (multiple - remainder);
            } else {
                return number - remainder;
            }
        } else {
            if (remainder >= -half_multiple + (multiple % 2)) {
                return number - remainder;
            } else {
                return number + (multiple - remainder);
            }
        }
    } else {
        if (multiple > 0) {
            if (-remainder >= half_multiple + (multiple % 2)) {
                return number - (multiple + remainder);
            } else {
                return number - remainder;
            }
        } else {
            if (-remainder >= -half_multiple + (multiple % 2)) {
                return number - remainder;
            } else {
                return number - (multiple + remainder);
            }
        }
    }
}

int main(void) {
    int test_cases[][2] = {
        {10, 3},
        {11, 3},
        {-10, 3},
        {-11, 3},
        {10, -3},
        {11, -3},
        {-10, -3},
        {-11, -3},
        {10, 0}
    };
    
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_cases; i++) {
        int number = test_cases[i][0];
        int multiple = test_cases[i][1];
        int result = round_to_nearest_multiple(number, multiple);
        printf("%d rounded to nearest multiple of %d is %d\n", number, multiple, result);
    }

    return 0;
}