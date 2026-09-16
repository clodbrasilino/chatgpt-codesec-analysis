#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int sum_common_divisors(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }

    int g = gcd(a, b);
    int sum = 0;

    for (int i = 1; i * i <= g; i++) {
        if (g % i == 0) {
            sum += i;
            if (i != g / i) {
                sum += g / i;
            }
        }
    }

    return sum;
}

int main(int argc, char * const argv[]) {
    int a, b;

    if (argc != 3) {
        if (scanf("%d %d", &a, &b) != 2) {
            return 1;
        }
    } else {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }

    if (a <= 0 || b <= 0) {
        return 1;
    }

    int result = sum_common_divisors(a, b);
    printf("%d\n", result);

    return 0;
}