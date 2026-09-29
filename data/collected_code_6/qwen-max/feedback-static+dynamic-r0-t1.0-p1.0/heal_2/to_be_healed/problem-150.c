#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_in_sequence(long long num) {
    long long a = 0, b = 1;
    while (a <= num && a >= 0 && b >= 0) {
        if (a == num) return true;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4660046610375530309 + 7540113804746346429 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:1383,execs:608,op:havoc,rep:4)
         */
        long long next = a + b;
        if (next < 0) break; // Check for overflow
        a = b;
        b = next;
    }
    return false;
}

int main() {
    long long n;
    printf("Enter a number: ");
    if (scanf("%lld", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (is_in_sequence(n)) {
        printf("The number is in the sequence.\n");
    } else {
        printf("The number is not in the sequence.\n");
    }
    return 0;
}