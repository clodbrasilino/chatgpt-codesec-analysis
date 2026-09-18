#include <stdio.h>
#include <stdlib.h>

unsigned long long permutation(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    
    unsigned long long result = 1;
    for (int i = 0; i < k; i++) {
        result *= (n - i);
    }
    
    return result;
}

int main(int argc, const char * const argv[]) {
    if (argc != 3) {
        printf("Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    unsigned long long p = permutation(n, k);
    
    if (p == 0 && (n < 0 || k < 0 || k > n)) {
        printf("Invalid input parameters.\n");
    } else {
        printf("P(%d, %d) = %llu\n", n, k, p);
    }
    
    return 0;
}