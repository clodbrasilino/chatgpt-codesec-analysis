#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  */

int count_unset_bits(unsigned int num) {
    int count = 0;
    int bits = sizeof(num) * CHAR_BIT;
    
    for (int i = 0; i < bits; i++) {
        if ((num & 1) == 0) {
            count++;
        }
        num >>= 1;
    }
    
    return count;
}

int main(void) {
    unsigned int number;
    
    printf("Enter a number: ");
    if (scanf("%u", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("%d\n", count_unset_bits(number));
    
    return 0;
}