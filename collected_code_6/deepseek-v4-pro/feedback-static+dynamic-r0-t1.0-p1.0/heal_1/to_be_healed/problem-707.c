#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 33, got <no output>
  *  test case 2 failed: expected 28, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  */

int countSetBits(int n) {
    int count = 0;
    int i = 0;
    int totalBits = sizeof(int) * 8;
    int power = 1;
    
    while (i < totalBits) {
        int totalPairs = (n + 1) / (power * 2);
        int remainder = (n + 1) % (power * 2);
        
        count += totalPairs * power;
        if (remainder > power) {
            count += remainder - power;
        }
        
        power <<= 1;
        i++;
    }
    
    return count;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:597,execs:293,op:havoc,rep:6; likely memory-safety defect
  */

int main(void) {
    int n;
    
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        printf("Please enter a non-negative number\n");
        return 1;
    }
    
    printf("Total set bits from 1 to %d: %d\n", n, countSetBits(n));
    
    return 0;
}