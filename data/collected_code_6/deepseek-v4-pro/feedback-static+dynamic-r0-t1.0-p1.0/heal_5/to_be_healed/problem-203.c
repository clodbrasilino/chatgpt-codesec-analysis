#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  */

int hamming_distance(int a, int b) {
    unsigned int xor_result = (unsigned int)a ^ (unsigned int)b;
    int distance = 0;
    
    while (xor_result != 0) {
        distance += xor_result & 1;
        xor_result >>= 1;
    }
    
    return distance;
}

static int safe_strtoint(const char *str, int *out) {
    char *endptr;
    long val;
    
    errno = 0;
    val = strtol(str, &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || endptr == str) {
        return 0;
    }
    
    if (val < INT_MIN || val > INT_MAX) {
        return 0;
    }
    
    *out = (int)val;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int num1, num2;
    
    if (!safe_strtoint(argv[1], &num1)) {
        fprintf(stderr, "Invalid integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    if (!safe_strtoint(argv[2], &num2)) {
        fprintf(stderr, "Invalid integer: %s\n", argv[2]);
        return EXIT_FAILURE;
    }
    
    int result = hamming_distance(num1, num2);
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}