#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

long long count_rectangles(int r) {
    if (r < 1) {
        return 0;
    }

    long long count = 0;
    long long r_sq = (long long)r * r;
    
    for (long long x = 1; x < r; x++) {
        long long y_max_sq = r_sq - x * x;
        /* Possible weaknesses found:
         *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'sqrt'
         *  call to undeclared library function 'sqrt' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        long long y_max = (long long)sqrt((double)y_max_sq);
        
        while (y_max >= 0 && y_max * y_max > y_max_sq) {
            y_max--;
        }
        while ((y_max + 1) * (y_max + 1) <= y_max_sq) {
            y_max++;
        }

        if (y_max >= r) {
            y_max = r - 1;
        }
        
        count += y_max;
    }

    return count * 4;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val < 0 || val > 10000) {
        return EXIT_FAILURE;
    }

    long long result = count_rectangles((int)val);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}