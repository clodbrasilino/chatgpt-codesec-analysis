#include <stdio.h>
#include <stdbool.h>

bool check_odd_parity(unsigned int num) {
    num ^= num >> 16;
    num ^= num >> 8;
    num ^= num >> 4;
    num ^= num >> 2;
    num ^= num >> 1;
    return (num & 1) == 1;
}

int main(void) {
    unsigned int val = 0;
    if (scanf("%u", &val) == 1) {
        if (check_odd_parity(val)) {
            printf("Odd Parity\n");
        } else {
            printf("Even Parity\n");
        }
        return 0;
    }
    return 1;
}