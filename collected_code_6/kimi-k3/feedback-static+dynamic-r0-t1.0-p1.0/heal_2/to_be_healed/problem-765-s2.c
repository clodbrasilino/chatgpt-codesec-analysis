#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 11, got <no output>
  *  test case 1 failed: expected 7, got <no output>
  *  test case 2 failed: expected 13, got <no output>
  */

int is_polite(unsigned long long num) {
    unsigned long long temp = num;
    while ((temp & 1) == 0) {
        temp >>= 1;
    }
    return temp > 1;
}

unsigned long long find_nth_polite(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned long long count = 0;
    unsigned long long num = 1;
    
    while (count < n) {
        if (is_polite(num)) {
            count++;
            if (count == n) {
                return num;
            }
        }
        
        if (num == ULLONG_MAX) {
            return 0;
        }
        num++;
    }
    
    return 0;
}

int main(void) {
    unsigned long long n;
    
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n == 0) {
        fprintf(stderr, "n must be positive\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = find_nth_polite(n);
    
    if (result == 0) {
        fprintf(stderr, "Result overflow or not found\n");
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}