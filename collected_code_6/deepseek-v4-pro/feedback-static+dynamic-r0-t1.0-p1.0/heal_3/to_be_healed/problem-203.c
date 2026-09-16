#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  */

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
int main(int argc, char *const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int result = hamming_distance(num1, num2);
    
    printf("Hamming distance between %d and %d is %d\n", num1, num2, result);
    
    return EXIT_SUCCESS;
}