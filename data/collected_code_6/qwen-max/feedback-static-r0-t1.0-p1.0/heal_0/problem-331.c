#include <stdio.h>

int count_unset_bits(unsigned int num) {
    int count = 0;
    while (num) {
        if (!(num & 1))
            count++;
        num >>= 1;
    }
    return count;
}

int main() {
    unsigned int number = 0x3F; // 00111111 in binary, as an example
    int result = count_unset_bits(number);
    printf("Number of unset bits: %d\n", result);
    return 0;
}