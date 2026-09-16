#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 0, got <no output>
  *  test case 0 failed: expected 3.5, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int min_jumps(int a, int b, int d) {
    if (d == 0) return 0;
    
    a = abs(a);
    b = abs(b);
    d = abs(d);
    
    if (a == 0 && b == 0) return -1;
    
    int max_step = (a > b) ? a : b;
    int min_step = (a < b) ? a : b;
    
    if (max_step == 0) return -1;
    
    int steps = d / max_step;
    int remainder = d % max_step;
    
    if (remainder == 0) {
        return steps;
    }
    
    if (remainder == min_step || remainder == max_step) {
        return steps + 1;
    }
    
    if (min_step == 0) return -1;
    
    if (remainder % min_step == 0) {
        int alt_steps = d / min_step;
        if (alt_steps < steps + 2) return alt_steps;
    }
    
    if (remainder + max_step == min_step) {
        return steps + 1;
    }
    
    return steps + 2;
}

int main(void) {
    int a, b, d;
    
    if (scanf("%d %d %d", &a, &b, &d) != 3) {
        return 1;
    }
    
    int result = min_jumps(a, b, d);
    printf("%d\n", result);
    
    return 0;
}