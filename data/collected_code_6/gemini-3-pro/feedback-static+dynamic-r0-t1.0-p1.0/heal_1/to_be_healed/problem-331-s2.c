#include <stdio.h>
#include <stdlib.h>

unsigned int count_unset_bits(unsigned int n);
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got 30
  *  test case 1 failed: expected 2, got 31
  *  test case 0 failed: expected 1, got 31
  */

unsigned int count_unset_bits(unsigned int n) {
    unsigned int count = 0;
    unsigned int total_bits = sizeof(n) * 8;
    
    for (unsigned int i = 0; i < total_bits; i++) {
        if ((n & (1U << i)) == 0) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    unsigned int number = 0;
    
    if (scanf("%u", &number) != 1) {
        return EXIT_FAILURE;
    }
    
    printf("%u\n", count_unset_bits(number));
    
    return EXIT_SUCCESS;
}