#include <stdio.h>
#include <stdbool.h>

bool check_odd_parity(unsigned int n) {
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count % 2 != 0;
}

int main() {
    unsigned int num;
    printf("Enter a number: ");
    if (scanf("%u", &num) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }

    if (check_odd_parity(num)) {
        printf("The number has odd parity.\n");
    } else {
        printf("The number does not have odd parity.\n");
    }

    return 0;
}