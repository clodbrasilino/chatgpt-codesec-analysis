#include <stdio.h>
#include <stdbool.h>

bool isProductEven(int n, ...) {
    va_list args;
    /* Possible weaknesses found:
     *  include the header <stdarg.h> or explicitly provide a declaration for 'va_start'
     *  call to undeclared library function 'va_start' with type 'void (struct __va_list_tag *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'va_start' [-Wimplicit-function-declaration]
     */
    va_start(args, n);
    for (int i = 0; i < n; ++i) {
        /* Possible weaknesses found:
         *  expected expression before 'int'
         *  implicit declaration of function 'va_arg' [-Wimplicit-function-declaration]
         *  call to undeclared function 'va_arg'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  expected expression
         */
        int num = va_arg(args, int);
        if (num % 2 == 0) {
            /* Possible weaknesses found:
             *  include the header <stdarg.h> or explicitly provide a declaration for 'va_end'
             *  call to undeclared library function 'va_end' with type 'void (struct __va_list_tag *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'va_end' [-Wimplicit-function-declaration]
             */
            va_end(args);
            return true;
        }
    }
    va_end(args);
    return false;
}

int main() {
    if (isProductEven(3, 2, 3, 5)) {
        printf("Product is even\n");
    } else {
        printf("Product is odd\n");
    }

    if (isProductEven(3, 1, 3, 5)) {
        printf("Product is even\n");
    } else {
        printf("Product is odd\n");
    }

    return 0;
}