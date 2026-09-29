#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL 10000000

int prime_factors_count[MAX_VAL] = {0};
int smart_numbers[MAX_VAL];
int total_smart_numbers = 0;

void precompute() {
    for (int i = 2; i < MAX_VAL; i++) {
        if (prime_factors_count[i] == 0) {
            for (int j = i; j < MAX_VAL; j += i) {
                prime_factors_count[j]++;
            }
        }
    }
    
    for (int i = 30; i < MAX_VAL; i++) {
        if (prime_factors_count[i] >= 3) {
            smart_numbers[total_smart_numbers++] = i;
        }
    }
}

int main(void) {
    precompute();
    
    int n;
    while (scanf("%d", &n) == 1) {
        if (n <= 0 || n > total_smart_numbers) {
            continue;
        }
        printf("%d\n", smart_numbers[n - 1]);
    }
    
    return 0;
}