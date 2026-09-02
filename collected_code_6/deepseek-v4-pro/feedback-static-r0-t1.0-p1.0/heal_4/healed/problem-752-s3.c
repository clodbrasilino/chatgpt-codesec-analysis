#include <stdio.h>
#include <stdlib.h>

long long jacobsthal(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    long long prev2 = 0;
    long long prev1 = 1;
    long long current = 0;
    
    for (int i = 2; i <= n; i++) {
        current = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
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