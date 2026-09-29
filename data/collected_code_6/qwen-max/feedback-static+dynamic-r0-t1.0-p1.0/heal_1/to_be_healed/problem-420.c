#include <stdio.h>
#include <stdlib.h>

long long cube_sum_of_evens(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        int even_number = 2 * i;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223013771341927200 + 796134035438568 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:306,execs:126,op:havoc,rep:3)
         */
        sum += (long long)even_number * even_number * even_number;
    }
    return sum;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    long long result = cube_sum_of_evens(n);
    printf("The cube sum of the first %d even natural numbers is: %lld\n", n, result);
    return EXIT_SUCCESS;
}