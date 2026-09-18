#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 13, got 1
  *  test case 0 failed: expected 11, got 1
  *  test case 1 failed: expected 7, got 0
  */

int is_polite(unsigned long long num) {
    if (num < 3) return 0;
    unsigned long long power = 1;
    while (power <= num) {
        if (power == num) return 0;
        if (power > num / 2) break;
        power <<= 1;
    }
    return 1;
}

unsigned long long nth_polite(int n) {
    if (n <= 0) return 0;
    
    unsigned long long count = 1;
    unsigned long long num = 3;
    
    while (1) {
        if (is_polite(num)) {
            if (count == (unsigned long long)n) return num;
            count++;
        }
        num++;
    }
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", nth_polite(n));
    
    return EXIT_SUCCESS;
}