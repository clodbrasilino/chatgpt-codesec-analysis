#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

long long cube_sum_of_even(uint32_t n) {
    if (n > (UINT32_MAX / 2)) {
        return -1;
    }
    long long sum = 0;
    for (uint32_t i = 1; i <= n; ++i) {
        long long temp = 2 * (long long)i;
        long long cube = temp * temp * temp;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223013771341927200 + 796134035438568 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:626,execs:275,op:havoc,rep:9)
         */
        if ((sum + cube) > LLONG_MAX) {
            return -1;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223013771341927200 + 796134035438568 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:626,execs:275,op:havoc,rep:9)
         */
        sum += cube;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of first even natural numbers: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    long long result = cube_sum_of_even(n);
    if (result == -1) {
        fprintf(stderr, "Input out of range. Please enter a smaller non-negative integer.\n");
        return EXIT_FAILURE;
    }
    printf("The cube sum of the first %d even natural numbers is: %lld\n", n, result);
    return EXIT_SUCCESS;
}