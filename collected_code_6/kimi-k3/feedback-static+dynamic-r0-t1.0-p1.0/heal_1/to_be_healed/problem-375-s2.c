#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <errno.h>

long round_to_nearest_multiple(long number, long multiple) {
    if (multiple == 0) {
        errno = EDOM;
        return 0;
    }
    
    if (number == 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000009,time:6520,execs:2983,op:havoc,rep:2)
     */
    long abs_multiple = labs(multiple);
    
    if (abs_multiple > LONG_MAX / 2) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000001,sig:06,src:000012,time:10501,execs:4762,op:havoc,rep:1)
         */
        if (labs(number) < abs_multiple / 2) {
            return 0;
        }
        return (number > 0) ? abs_multiple : -abs_multiple;
    }
    
    long remainder = number % abs_multiple;
    long half_multiple = abs_multiple / 2;
    
    if (labs(remainder) <= half_multiple) {
        return number - remainder;
    }
    
    if (number > 0) {
        if (number > LONG_MAX - abs_multiple) {
            errno = ERANGE;
            return number;
        }
        return number - remainder + abs_multiple;
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -9223372036854775808 + -9223372036854775808 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000009,time:6520,execs:2983,op:havoc,rep:2)
         */
        if (number < LONG_MIN + abs_multiple) {
            errno = ERANGE;
            return number;
        }
        return number - remainder - abs_multiple;
    }
}

int main(void) {
    long number, multiple, result;
    
    printf("Enter number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter multiple: ");
    if (scanf("%ld", &multiple) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    result = round_to_nearest_multiple(number, multiple);
    
    if (errno == EDOM) {
        fprintf(stderr, "Error: Multiple cannot be zero\n");
        return EXIT_FAILURE;
    }
    
    if (errno == ERANGE) {
        fprintf(stderr, "Warning: Result would overflow, returning original number\n");
    }
    
    printf("Result: %ld\n", result);
    
    return EXIT_SUCCESS;
}