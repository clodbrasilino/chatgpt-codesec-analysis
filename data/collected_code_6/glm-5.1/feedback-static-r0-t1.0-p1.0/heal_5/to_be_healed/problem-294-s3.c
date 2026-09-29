#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double find_max(int count, ...) {
    if (count <= 0) {
        exit(EXIT_FAILURE);
    }

    va_list args;
    /* Possible weaknesses found:
     *  include the header <stdarg.h> or explicitly provide a declaration for 'va_start'
     *  implicit declaration of function 'va_start' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'va_start' with type 'void (struct __va_list_tag *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    va_start(args, count);

    double max_val = -DBL_MAX;
    
    for (int i = 0; i < count; i++) {
        /* Possible weaknesses found:
         *  call to undeclared function 'va_arg'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  expected expression before 'int'
         *  implicit declaration of function 'va_arg' [-Wimplicit-function-declaration]
         *  expected expression
         */
        int type = va_arg(args, int);
        
        if (type == 0) {
            /* Possible weaknesses found:
             *  expected expression before 'int'
             *  expected expression
             */
            int val = va_arg(args, int);
            if (val > max_val) {
                max_val = val;
            }
        } else if (type == 1) {
            /* Possible weaknesses found:
             *  expected expression before 'double'
             *  expected expression
             */
            double val = va_arg(args, double);
            if (val > max_val) {
                max_val = val;
            }
        } else {
            /* Possible weaknesses found:
             *  include the header <stdarg.h> or explicitly provide a declaration for 'va_end'
             *  call to undeclared library function 'va_end' with type 'void (struct __va_list_tag *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'va_end' [-Wimplicit-function-declaration]
             */
            va_end(args);
            exit(EXIT_FAILURE);
        }
    }
    
    /* Possible weaknesses found:
     *  va_list 'args' used before va_start() was called. [va_list_usedBeforeStarted]
     */
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