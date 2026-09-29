#include<stdio.h>

int nc2(int n) {
    if(n == 0) {
        return 1;
    } else {
        return n * nc2(n - 1) / (2 * (n - 1) + 1);
    }
}

int binary_sequences_count(int n) {
    int result = 0, count;
    for(count = 0; count <= n; count++) {
        result += nc2(count) * nc2(n - count);
    }
    result *= result;
    return result;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Count of binary sequences of length 2n, such that sum of first n bits = sum of last n bits, is %d", binary_sequences_count(n));
    return 0;
}