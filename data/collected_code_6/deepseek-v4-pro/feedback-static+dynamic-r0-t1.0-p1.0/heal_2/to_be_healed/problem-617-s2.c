#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3.5, got 3
  */

int min_jumps(int a, int b, int d) {
    if (a == 0 && b == 0 && d == 0) return 0;
    if (a == 0 && b == 0 && d != 0) return -1;
    
    int max_step = abs(a) > abs(b) ? abs(a) : abs(b);
    int target = abs(d);
    
    if (max_step == 0) return -1;
    
    if (target == 0) return 0;
    
    int steps = target / max_step;
    if (target % max_step != 0) {
        steps += 1;
    }
    
    return steps;
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