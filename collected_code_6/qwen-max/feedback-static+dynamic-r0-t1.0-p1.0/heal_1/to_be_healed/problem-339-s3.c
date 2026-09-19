#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 2, got 1
  */

int findMaxDivisor(int start, int end) {
    if (start > end) {
        int temp = start;
        start = end;
        end = temp;
    }
    
    int max_divisor = 1;
    int divisor_count[1001] = {0};
    
    for (int i = start; i <= end; ++i) {
        for (int j = i + 1; j <= end; ++j) {
            int current_gcd = gcd(i, j);
            if (current_gcd > 1) {
                divisor_count[current_gcd]++;
                if (divisor_count[current_gcd] > divisor_count[max_divisor]) {
                    max_divisor = current_gcd;
                }
            }
        }
    }
    
    return max_divisor;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:7,execs:15,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int start, end;
    printf("Enter the start and end of the interval: ");
    scanf("%d %d", &start, &end);
    
    int result = findMaxDivisor(start, end);
    printf("The maximum occurring divisor in the interval is: %d\n", result);
    
    return 0;
}