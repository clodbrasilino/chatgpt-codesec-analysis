#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long long lucas_number(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    int64_t a = 2, b = 1;
    for (int i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3980154972736918051 + 6440026026380244498 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:808,execs:268,op:havoc,rep:7)
         */
        int64_t c = a + b;
        a = b;
        b = c;
    }
    return (long long)b;
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