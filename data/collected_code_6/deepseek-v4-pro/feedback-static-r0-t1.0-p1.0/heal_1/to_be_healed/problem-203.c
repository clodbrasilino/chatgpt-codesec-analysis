#include <stdio.h>
#include <stdlib.h>

int hamming_distance(int a, int b) {
    int xor_result = a ^ b;
    int distance = 0;
    
    while (xor_result != 0) {
        distance += xor_result & 1;
        xor_result >>= 1;
    }
    
    return distance;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int num1 = atoi(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int num2 = atoi(argv[2]);
    int result = hamming_distance(num1, num2);
    
    printf("Hamming distance between %d and %d is %d\n", num1, num2, result);
    
    return EXIT_SUCCESS;
}