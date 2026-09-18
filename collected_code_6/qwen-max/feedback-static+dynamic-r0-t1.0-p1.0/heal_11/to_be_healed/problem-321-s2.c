#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long calculateDemloNumber(int n) {
    long long result = 0;
    long long multiplier = 1;
    for (int i = n; i > 0; i--) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -6534447704509133831 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:58,execs:34,op:havoc,rep:4)
         * UBSan: signed integer overflow: 3331137 * 11111111111111 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:58,execs:34,op:havoc,rep:4)
         */
        if (result > LLONG_MAX - (i * multiplier)) return -1;
        if (multiplier > LLONG_MAX / 10 || (multiplier == LLONG_MAX / 10 && i > LLONG_MAX % 10)) return -1;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3331137 * 11111111111111 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:58,execs:34,op:havoc,rep:4)
         */
        result += (i * multiplier);
        if (multiplier > LLONG_MAX / 11) return -1;
        if (LLONG_MAX / 10 < multiplier) return -1;
        multiplier = multiplier * 10 + 1;
    }
    return result;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1 || number <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    long long demloNumber = calculateDemloNumber(number);
    if (demloNumber == -1) {
        fprintf(stderr, "Calculation overflowed. Please enter a smaller number.\n");
        return EXIT_FAILURE;
    }
    printf("The Demlo number of %d is %lld\n", number, demloNumber);
    return EXIT_SUCCESS;
}