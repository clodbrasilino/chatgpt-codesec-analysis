#include <stdio.h>
#include <stdlib.h>

long long calculate_electricity_bill(int units) {
    if (units < 0) {
        return -1;
    }

    if (units <= 100) {
        return (long long)units * 1;
    } else if (units <= 200) {
        return 100LL * 1 + (long long)(units - 100) * 2;
    } else if (units <= 300) {
        return 100LL * 1 + 100LL * 2 + (long long)(units - 200) * 3;
    } else {
        return 100LL * 1 + 100LL * 2 + 100LL * 3 + (long long)(units - 300) * 5;
    }
}

int main() {
    int units;
    if (scanf("%d", &units) != 1) {
        return 1;
    }

    long long bill = calculate_electricity_bill(units);

    if (bill < 0) {
        return 1;
    }

    printf("%lld\n", bill);

    return 0;
}