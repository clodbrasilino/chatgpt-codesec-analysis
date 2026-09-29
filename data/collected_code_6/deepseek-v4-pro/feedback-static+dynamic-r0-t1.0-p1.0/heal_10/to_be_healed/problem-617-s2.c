#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3.5, got 3
  */

double min_jumps(int a, int b, int d) {
    if (d == 0) return 0.0;
    
    a = abs(a);
    b = abs(b);
    d = abs(d);
    
    if (a == 0 && b == 0) return -1.0;
    
    double da = (double)a;
    double db = (double)b;
    double dd = (double)d;
    
    if (da == 0.0 && db == 0.0) return -1.0;
    
    if (da == 0.0 || db == 0.0) {
        double non_zero = (da > 0.0) ? da : db;
        if (fmod(dd, non_zero) == 0.0) {
            return dd / non_zero;
        }
        return -1.0;
    }
    
    double max_step = (da > db) ? da : db;
    double min_step = (da < db) ? da : db;
    
    if (min_step == 0.0) return -1.0;
    
    double min_jumps = DBL_MAX;
    
    int max_count = (int)(dd / min_step);
    for (int i = 0; i <= max_count; i++) {
        double remaining = dd - i * min_step;
        if (fmod(remaining, max_step) == 0.0) {
            double j = remaining / max_step;
            double total = i + j;
            if (total < min_jumps) {
                min_jumps = total;
            }
        }
    }
    
    if (min_jumps == DBL_MAX) {
        return -1.0;
    }
    
    return min_jumps;
}

int main(void) {
    int a, b, d;
    
    if (scanf("%d %d %d", &a, &b, &d) != 3) {
        return 1;
    }
    
    double result = min_jumps(a, b, d);
    if (result == (int)result) {
        printf("%d\n", (int)result);
    } else {
        printf("%.1f\n", result);
    }
    
    return 0;
}