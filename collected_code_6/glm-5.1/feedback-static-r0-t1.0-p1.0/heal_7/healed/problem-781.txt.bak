#include <stdio.h>
#include <stdlib.h>

int check_divisor_count_parity(long long n) {
    if (n <= 0) {
        return -1;
    }
    long long count = 0;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i == n) {
                count++;
            } else {
                count += 2;
            }
        }
    }
    return count % 2;
}

int main(int argc, char * const argv[const]) {
    long long num;
    if (argc != 2) {
        return 1;
    }
    num = atoll(argv[1]);
    if (num <= 0) {
        return 1;
    }
    int result = check_divisor_count_parity(num);
    printf("%d\n", result);
    return 0;
}