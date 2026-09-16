#include <stdio.h>

unsigned long long sum_of_fifth_powers(int n) {
    unsigned long long sum = 0;
    int i = 1;
    while (n > 0) {
        sum += (2 * i) * (2 * i) * (2 * i) * (2 * i) * (2 * i);
        i++;
        n--;
    }
    return sum;
}

int main() {
    int n;
    scanf("%d", &n);
    if (n <= 0) {
        printf("Enter a positive integer.\n");
        return 1;
    }
    unsigned long long result = sum_of_fifth_powers(n);
    printf("%llu\n", result);
    return 0;
}