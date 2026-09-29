#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 2, got <no output>
  *  test case 1 failed: expected 1, got <no output>
  */

int count_set_bits(unsigned int num) {
    int count = 0;
    while (num != 0U) {
        count += (int)(num & 1U);
        num >>= 1;
    }
    return count;
}

int main(void) {
    unsigned int number;
    int result;
    
    if (scanf("%u", &number) != 1) {
        return 1;
    }
    
    result = count_set_bits(number);
    
    if (printf("%d\n", result) < 0) {
        return 1;
    }
    
    return 0;
}