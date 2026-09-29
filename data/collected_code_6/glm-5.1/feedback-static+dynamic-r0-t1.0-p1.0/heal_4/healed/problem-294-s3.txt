#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <float.h>

double find_max(int count, ...) {
    if (count <= 0) {
        exit(EXIT_FAILURE);
    }

    va_list args;
    va_start(args, count);

    double max_val = -DBL_MAX;
    
    for (int i = 0; i < count; i++) {
        int type = va_arg(args, int);
        
        if (type == 0) {
            int val = va_arg(args, int);
            if (val > max_val) {
                max_val = val;
            }
        } else if (type == 1) {
            double val = va_arg(args, double);
            if (val > max_val) {
                max_val = val;
            }
        } else {
            va_end(args);
            exit(EXIT_FAILURE);
        }
    }
    
    va_end(args);
    
    return max_val;
}

int main(void) {
    double result1 = find_max(5, 0, 10, 1, 3.14, 0, -5, 1, 99.5);
    double result2 = find_max(3, 0, -10, 0, -20, 0, -5);
    
    printf("%f\n", result1);
    printf("%f\n", result2);
    
    return 0;
}