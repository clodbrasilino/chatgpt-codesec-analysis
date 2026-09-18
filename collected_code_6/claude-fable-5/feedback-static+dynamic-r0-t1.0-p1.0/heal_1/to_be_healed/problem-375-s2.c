#include <stdio.h>
#include <stdlib.h>

long round_to_nearest_multiple(long number, long multiple)
{
    long remainder;
    long half;

    if (multiple == 0) {
        return number;
    }

    if (multiple < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000002,sig:06,src:000009,time:15987,execs:9543,op:havoc,rep:2)
         */
        multiple = -multiple;
    }

    remainder = number % multiple;

    if (remainder == 0) {
        return number;
    }

    half = multiple / 2;

    if (number >= 0) {
        if (remainder >= multiple - half) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 9223372036854775807 + 2 cannot be represented in type 'long' (AFL crash: id:000003,sig:06,src:000007,time:27722,execs:15850,op:havoc,rep:1)
             * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000003,time:7923,execs:4870,op:havoc,rep:1)
             */
            return number + (multiple - remainder);
        }
        return number - remainder;
    }

    if (-remainder >= multiple - half) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -9223372036854775808 + -7 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000009,time:15987,execs:9543,op:havoc,rep:2)
         * UBSan: signed integer overflow: -9223372036854775808 - 1 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000009,time:13809,execs:8291,op:havoc,rep:1)
         */
        return number - (multiple + remainder);
    }
    return number - remainder;
}

int main(void)
{
    long number;
    long multiple;
    long result;

    printf("Enter the number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input for number\n");
        return EXIT_FAILURE;
    }

    printf("Enter the multiple: ");
    if (scanf("%ld", &multiple) != 1) {
        fprintf(stderr, "Invalid input for multiple\n");
        return EXIT_FAILURE;
    }

    if (multiple == 0) {
        fprintf(stderr, "Multiple must not be zero\n");
        return EXIT_FAILURE;
    }

    result = round_to_nearest_multiple(number, multiple);

    printf("%ld rounded to the nearest multiple of %ld is %ld\n", number, multiple, result);

    return EXIT_SUCCESS;
}