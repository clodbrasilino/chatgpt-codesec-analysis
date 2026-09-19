#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t tile(int n) {
    if (n == 0 || n == 1) return 1;
    int64_t a = 1, b = 1, c = 0;
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4660046610375530309 + 7540113804746346429 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:308,execs:282,op:havoc,rep:2)
         */
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int main() {
    int n;
    printf("Enter the number of tiles: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        fprintf(stderr, "Number of tiles cannot be negative\n");
        return EXIT_FAILURE;
    }
    int64_t result = tile(n);
    /* Possible weaknesses found:
     *  %lld in format string (no. 1) requires 'long long' but the argument type is 'signed long'. [invalidPrintfArgType_sint]
     */
    printf("The number of ways to tile the floor is: %lld\n", result);
    return EXIT_SUCCESS;
}