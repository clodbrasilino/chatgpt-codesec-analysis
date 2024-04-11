#include <stdio.h>

int hammingDistance(int n1, int n2) {
    int x = n1 ^ n2;
    int setBits = 0;

    while (x > 0) {
        setBits += x & 1;
        x >>= 1;
    }

    return setBits;
}

int sumHamming(int n) {
    int sum = 0;
    for (int i = 0; i <= n; i++)
        for (int j = i+1; j <= n; j++)
            sum += hammingDistance(i, j);
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of hamming distances is: %d\n", sumHamming(n));
    return 0;
}