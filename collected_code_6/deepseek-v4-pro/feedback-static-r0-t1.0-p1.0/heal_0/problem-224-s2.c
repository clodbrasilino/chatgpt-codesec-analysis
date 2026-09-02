#include <stdio.h>

int count_set_bits(unsigned int num) {
    int count = 0;
    while (num != 0) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

int main(void) {
    unsigned int test_num = 0b11001010;
    int result = count_set_bits(test_num);
    printf("Number of set bits in %u: %d\n", test_num, result);
    return 0;
}