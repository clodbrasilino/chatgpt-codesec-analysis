#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int int_part = 42;
    int frac_part = 567;

    if (argc >= 3) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        int_part = atoi(argv[1]);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        frac_part = atoi(argv[2]);
    }

    double result = tuple_to_float(int_part, frac_part);
    
    if (result != -1.0 || (int_part == -1 && frac_part == 0)) {
        printf("%f\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}