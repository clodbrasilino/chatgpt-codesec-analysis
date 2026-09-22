#include <stdio.h>
#include <math.h>

int is_woodall(long n) {
    for (long k = 1; ; ++k) {
        long woodall_number = k * pow(2, k) - 1;
        if (woodall_number == n) return 1;
        if (woodall_number > n || woodall_number < 0) break;
    }
    return 0;
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);

    if (is_woodall(number)) {
        printf("%ld is a Woodall number.\n", number);
    } else {
        printf("%ld is not a Woodall number.\n", number);
    }

    return 0;
}