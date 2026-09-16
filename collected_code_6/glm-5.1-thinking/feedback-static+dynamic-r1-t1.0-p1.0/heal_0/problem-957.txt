#include <stdio.h>

int get_rightmost_set_bit_position(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    unsigned int rightmost_bit = n & (~n + 1);
    int position = 0;
    while (rightmost_bit > 0) {
        position++;
        rightmost_bit >>= 1;
    }
    return position;
}

int main(void) {
    unsigned int num = 12;
    int result = get_rightmost_set_bit_position(num);
    printf("%d\n", result);
    return 0;
}