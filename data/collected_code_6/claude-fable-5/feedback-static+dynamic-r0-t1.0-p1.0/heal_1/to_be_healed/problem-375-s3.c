#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long round_to_nearest_multiple(long number, long multiple, int *error)
{
    if (multiple == 0) {
        *error = 1;
        return 0;
    }

    *error = 0;

    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000001,sig:06,src:000007,time:3715,execs:2284,op:havoc,rep:1)
     */
    long abs_multiple = labs(multiple);
    long remainder = number % abs_multiple;

    if (remainder == 0) {
        return number;
    }

    long lower = number - remainder;
    long upper;

    if (number >= 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775806 + 2 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000003,time:1089,execs:672,op:havoc,rep:1)
         * UBSan: signed integer overflow: 9223372036854775800 + 9 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000007,time:3789,execs:2330,op:havoc,rep:1)
         */
        upper = lower + abs_multiple;
    } else {
        upper = lower;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -9223372036854775800 - 9 cannot be represented in type 'long' (AFL crash: id:000003,sig:06,src:000008,time:18452,execs:10770,op:havoc,rep:3)
         */
        lower = upper - abs_multiple;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -9223372036854775808 - 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000003,time:1089,execs:672,op:havoc,rep:1)
     * UBSan: signed integer overflow: -9223372036854775807 - 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000002,sig:06,src:000007,time:3789,execs:2330,op:havoc,rep:1)
     * UBSan: signed integer overflow: -9223372036854775808 - 2 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000007,time:3715,execs:2284,op:havoc,rep:1)
     * UBSan: signed integer overflow: -9223372036854775808 - 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000003,sig:06,src:000008,time:18452,execs:10770,op:havoc,rep:3)
     */
    if (number - lower < upper - number) {
        return lower;
    }
    return upper;
}

int main(void)
{
    long number;
    long multiple;
    int error;

    printf("Enter the number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input for number.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the multiple: ");
    if (scanf("%ld", &multiple) != 1) {
        fprintf(stderr, "Invalid input for multiple.\n");
        return EXIT_FAILURE;
    }

    long result = round_to_nearest_multiple(number, multiple, &error);

    if (error != 0) {
        fprintf(stderr, "Error: multiple cannot be zero.\n");
        return EXIT_FAILURE;
    }

    printf("%ld rounded to the nearest multiple of %ld is %ld\n",
           number, multiple, result);

    return EXIT_SUCCESS;
}