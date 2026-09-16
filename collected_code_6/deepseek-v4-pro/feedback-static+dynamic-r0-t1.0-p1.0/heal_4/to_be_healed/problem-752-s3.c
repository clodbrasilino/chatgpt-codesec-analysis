#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 1, got <no output>
  *  test case 2 failed: expected 5, got <no output>
  *  test case 0 failed: expected 11, got <no output>
  */

long long jacobsthal(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    long long prev2 = 0;
    long long prev1 = 1;
    /* Possible weaknesses found:
     *  Variable 'current' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'current' can be reduced. [variableScope]
     */
    long long current = 0;
    
    for (int i = 2; i <= n; i++) {
        current = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val < 0 || val > 50) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    int n = (int)val;
    printf("%lld\n", jacobsthal(n));
    return 0;
}