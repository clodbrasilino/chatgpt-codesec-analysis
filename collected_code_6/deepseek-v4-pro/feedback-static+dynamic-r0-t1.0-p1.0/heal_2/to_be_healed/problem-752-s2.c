#include <stdlib.h>
#include <stdio.h>

unsigned long long jacobsthal(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    unsigned long long prev2 = 0;
    unsigned long long prev1 = 1;
    unsigned long long curr = 0;
    
    for (int i = 2; i <= n; i++) {
        curr = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    
    return curr;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 63) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%llu\n", jacobsthal((int)val));
    return 0;
}