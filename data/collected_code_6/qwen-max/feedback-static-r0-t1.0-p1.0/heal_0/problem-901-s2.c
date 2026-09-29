#include <stdio.h>
#include <stdlib.h>

long long lcm(long long a, long long b) {
    long long max = (a > b) ? a : b;
    while(1) {
        if(max % a == 0 && max % b == 0)
            return max;
        ++max;
    }
}

long long smallestMultiple(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result = lcm(result, i);
    }
    return result;
}

int main() {
    int n = 10; // Example: Find the smallest multiple of the first 10 numbers
    printf("The smallest multiple of the first %d numbers is: %lld\n", n, smallestMultiple(n));
    return 0;
}