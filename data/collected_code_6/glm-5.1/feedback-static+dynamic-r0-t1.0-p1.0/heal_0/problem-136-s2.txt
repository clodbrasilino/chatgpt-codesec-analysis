#include <stdio.h>

int calculate_electricity_bill(int units) {
    if (units < 0) {
        return -1;
    }

    if (units <= 100) {
        return units * 1;
    } else if (units <= 200) {
        return 100 * 1 + (units - 100) * 2;
    } else if (units <= 300) {
        return 100 * 1 + 100 * 2 + (units - 200) * 3;
    } else {
        return 100 * 1 + 100 * 2 + 100 * 3 + (units - 300) * 5;
    }
}

int main() {
    int units;
    if (scanf("%d", &units) != 1) {
        return 1;
    }

    int bill = calculate_electricity_bill(units);

    if (bill < 0) {
        return 1;
    }

    printf("%d\n", bill);

    return 0;
}