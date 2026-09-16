#include <stdio.h>
#include <limits.h>

unsigned int toggle_first_last(unsigned int num) {
    unsigned int mask = 0;
    if (sizeof(unsigned int) * CHAR_BIT > 0) {
        mask |= 1u;
        mask |= (1u << (sizeof(unsigned int) * CHAR_BIT - 1));
    }
    return num ^ mask;
}

int main() {
    unsigned int val = 0;
    unsigned int res = toggle_first_last(val);
    printf("%u\n", res);
    val = 1;
    res = toggle_first_last(val);
    printf("%u\n", res);
    val = 2147483648;
    res = toggle_first_last(val);
    printf("%u\n", res);
    return 0;
}