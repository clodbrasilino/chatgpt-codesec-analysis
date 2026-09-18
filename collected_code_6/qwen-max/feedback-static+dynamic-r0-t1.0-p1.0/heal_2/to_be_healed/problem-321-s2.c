#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long calculateDemloNumber(int n) {
    long long result = 0;
    long long multiplier = 1;
    for (int i = n; i > 0; i--) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 111105 * 111111111111111 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:23,execs:12,op:havoc,rep:6)
         * UBSan: signed integer overflow: 795 * 111111111111111111 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:933,execs:372,op:havoc,rep:8)
         * UBSan: signed integer overflow: 984087791495197372 + 8844444444444444356 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:933,execs:372,op:havoc,rep:8)
         * UBSan: signed integer overflow: -4730063689621959026 + -5678319627077984768 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:23,execs:12,op:havoc,rep:6)
         */
        result += (i * multiplier);
        if (multiplier > LLONG_MAX / 10) {
            return -1;
        }
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