#include <stdio.h>
#include <stdlib.h>

long sum_of_fourth_powers(int n) {
    long sum = 0;
    int i;
    for (i = 1; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 10077696 * 216 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:354,execs:152,op:havoc,rep:7)
         */
        sum += (2 * i) * (2 * i) * (2 * i) * (2 * i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    long result = sum_of_fourth_powers(n);
    printf("The sum of the fourth powers of the first %d even natural numbers is: %ld\n", n, result);
    return EXIT_SUCCESS;
}