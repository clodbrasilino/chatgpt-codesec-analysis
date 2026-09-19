#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

long long lucas_number(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    long long a = 2, b = 1;
    for (int i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3980154972736918051 + 6440026026380244498 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:141,execs:142,op:havoc,rep:4)
         */
        long long c = a + b;
        if (c < a || c < b) {
            fprintf(stderr, "Overflow detected\n");
            exit(EXIT_FAILURE);
        }
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    printf("Enter the position of the Lucas number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }

    long long result = lucas_number(n);
    printf("The %dth Lucas number is: %lld\n", n, result);

    return EXIT_SUCCESS;
}