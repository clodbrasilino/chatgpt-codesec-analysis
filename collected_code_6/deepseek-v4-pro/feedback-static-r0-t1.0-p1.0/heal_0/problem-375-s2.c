#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int round_to_multiple(int number, int multiple) {
    if (multiple == 0) {
        return number;
    }
    
    int abs_multiple = abs(multiple);
    int remainder = number % abs_multiple;
    
    if (remainder == 0) {
        return number;
    }
    
    int abs_remainder = abs(remainder);
    int half = abs_multiple / 2;
    
    if (abs_remainder >= half + (abs_multiple % 2)) {
        if ((number > 0 && multiple > 0) || (number < 0 && multiple < 0)) {
            return number + (abs_multiple - abs_remainder) * (number > 0 ? 1 : -1);
        } else {
            return number - (abs_multiple - abs_remainder) * (number > 0 ? 1 : -1);
        }
    } else {
        return number - remainder;
    }
}

int main(void) {
    int test_cases[][3] = {
        {17, 5, 0},
        {14, 7, 0},
        {23, 10, 0},
        {-7, 3, 0},
        {22, 4, 0},
        {0, 5, 0},
        {19, 0, 0}
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int result = round_to_multiple(test_cases[i][0], test_cases[i][1]);
        printf("%d rounded to nearest multiple of %d is %d\n", 
               test_cases[i][0], test_cases[i][1], result);
    }
    
    return 0;
}