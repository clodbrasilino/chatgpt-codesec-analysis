#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 31
  *  test case 2 failed: expected 1, got 30
  *  test case 1 failed: expected 2, got 31
  */

int countUnsetBits(unsigned int num) {
    int count = 0;
    int totalBits = sizeof(num) * CHAR_BIT;
    
    for (int i = 0; i < totalBits; i++) {
        if ((num & (1U << i)) == 0) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    unsigned int num;
    
    if (scanf("%u", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    int result = countUnsetBits(num);
    printf("%d\n", result);
    
    return 0;
}