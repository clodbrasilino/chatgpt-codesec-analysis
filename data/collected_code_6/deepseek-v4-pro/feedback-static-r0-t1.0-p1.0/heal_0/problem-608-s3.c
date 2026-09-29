#include <stdio.h>
#include <stdlib.h>

long long bell_number(int n) {
    if (n < 0) return -1;
    if (n == 0) return 1;
    
    long long *bell = (long long *)calloc(n + 1, sizeof(long long));
    if (bell == NULL) return -1;
    
    bell[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        long long prev = bell[0];
        bell[0] = bell[i - 1];
        for (int j = 1; j <= i; j++) {
            long long temp = bell[j];
            bell[j] = prev + bell[j - 1];
            prev = temp;
        }
    }
    
    long long result = bell[n];
    free(bell);
    return result;
}

int main() {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    long long result = bell_number(n);
    if (result == -1 && n < 0) {
        fprintf(stderr, "n must be non-negative\n");
        return 1;
    }
    
    printf("Bell number B%d = %lld\n", n, result);
    return 0;
}