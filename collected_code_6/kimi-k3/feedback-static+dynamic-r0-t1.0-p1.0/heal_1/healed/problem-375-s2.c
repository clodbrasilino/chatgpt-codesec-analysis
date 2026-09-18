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
    
    unsigned long uabs_multiple;
    if (multiple == LONG_MIN) {
        uabs_multiple = (unsigned long)LONG_MAX + 1UL;
    } else {
        uabs_multiple = (unsigned long)labs(multiple);
    }
    
    if (uabs_multiple > (unsigned long)LONG_MAX / 2UL) {
        unsigned long uabs_number;
        if (number == LONG_MIN) {
            uabs_number = (unsigned long)LONG_MAX + 1UL;
        } else {
            uabs_number = (unsigned long)labs(number);
        }
        
        if (uabs_number < uabs_multiple / 2UL) {
            return 0;
        }
        
        if (uabs_multiple == (unsigned long)LONG_MAX + 1UL) {
            if (number > 0) {
                errno = ERANGE;
                return number;
            } else {
                return LONG_MIN;
            }
        }
        
        return (number > 0) ? (long)uabs_multiple : -(long)uabs_multiple;
    }
    
    long abs_multiple = (long)uabs_multiple;
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