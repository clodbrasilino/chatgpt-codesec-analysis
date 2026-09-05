#include <stdio.h>
#include <stdlib.h>

int sum_even_factors(int n) {
    if (n <= 0) {
        return 0;
    }

    int sum = 0;
    for (int i = 2; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            int complement = n / i;
            if (complement != i && complement % 2 == 0) {
                sum += complement;
            }
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val <= 0 || val > 2147483647) {
        return 1;
    }

    int num = (int)val;
    int result = sum_even_factors(num);
    printf("%d\n", result);

    return 0;
}