#include <stdio.h>
#include <stdbool.h>

bool check_odd_parity(unsigned int num) {
    unsigned int cnt = 0;
    while (num) {
        cnt += num & 1;
        num >>= 1;
    }
    return (cnt % 2) == 1;
}

int main() {
    unsigned int number = 0xAAAA; // Example number
    if (check_odd_parity(number)) {
        printf("The number has odd parity.\n");
    } else {
        printf("The number does not have odd parity.\n");
    }
    return 0;
}