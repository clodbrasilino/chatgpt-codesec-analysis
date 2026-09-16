#include <stdio.h>
#include <stdlib.h>

unsigned long long findNthSmartNumber(int n) {
    if (n <= 0) {
        return 0;
    }
    int max_approx = n * 10;
    int *divisors = (int *)calloc(max_approx + 1, sizeof(int));
    if (divisors == NULL) {
        return 0;
    }
    for (int i = 2; i <= max_approx; i++) {
        if (divisors[i] == 0) {
            for (int j = i; j <= max_approx; j += i) {
                divisors[j]++;
            }
        }
    }
    int count = 0;
    unsigned long long result = 0;
    for (int i = 1; i <= max_approx; i++) {
        if (divisors[i] >= 3) {
            count++;
            if (count == n) {
                result = (unsigned long long)i;
                break;
            }
        }
    }
    free(divisors);
    divisors = NULL;
    return result;
}

int main() {
    int n = 10;
    unsigned long long smart_number = findNthSmartNumber(n);
    if (smart_number != 0) {
        printf("%llu\n", smart_number);
    } else {
        printf("0\n");
    }
    return 0;
}