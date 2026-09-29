#include <stdio.h>
#include <stdlib.h>

int f(int n, int *cache) {
    if (n < 2) return n;
    if (cache[n] != -1) return cache[n];
    
    int a = f(n / 2, cache);
    int b = f(n / 3, cache);
    int c = f(n / 4, cache);
    int d = f(n / 5, cache);
    
    int sum = a + b + c + d;
    cache[n] = (sum > n) ? sum : n;
    
    return cache[n];
}

int main() {
    int n;
    scanf("%d", &n);
    
    int *cache = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        cache[i] = -1;
    }
    
    int result = f(n, cache);
    printf("%d\n", result);
    
    free(cache);
    return 0;
}