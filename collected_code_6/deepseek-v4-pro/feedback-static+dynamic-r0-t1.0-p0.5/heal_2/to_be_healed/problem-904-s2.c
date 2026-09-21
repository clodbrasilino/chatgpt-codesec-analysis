#include <stdbool.h>
#include <stdlib.h>

bool is_even(int number) {
    return number % 2 == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int test_number = 0;
    
    if (argc > 1) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        test_number = atoi(argv[1]);
    } else {
        test_number = 42;
    }
    
    if (is_even(test_number)) {
        return 0;
    }
    
    return 1;
}