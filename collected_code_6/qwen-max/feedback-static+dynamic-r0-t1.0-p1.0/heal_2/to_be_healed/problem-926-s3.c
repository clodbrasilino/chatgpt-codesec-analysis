#include <stdio.h>
#include <stdbool.h>

bool is_input_valid(long n) {
    return n >= 0;
}

long derangement(long n) {
    long a = 1, b = 0;
    for (long i = 0; i <= n; ++i) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 20 * 939765362752547227 cannot be represented in type 'long' (AFL crash: id:000000,sig:06,src:000002,time:127,execs:129,op:havoc,rep:1)
         */
        long temp = (i + 1) * (a + b);
        if ((i + 1) > 0 && (a + b) > 0 && (temp / (i + 1)) != (a + b)) return -1;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1 || !is_input_valid(n)) return 1;
    long result = derangement(n);
    if (result == -1) {
        printf("Error: Integer overflow detected.\n");
    } else {
        printf("The %ld-th derangement number is: %ld\n", n, result);
    }
    return 0;
}