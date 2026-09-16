#include <stdio.h>
#include <limits.h>

int find_most_significant_set_bit(unsigned int num) {
    int msb = -1;
    for (int i = 31; i >= 0; --i) {
        if (num & (1 << i)) {
            msb = i;
            break;
        }
    }
    return msb;
}

int main(void) {
    unsigned int num = 18;
    int result = find_most_significant_set_bit(num);
    if (result != -1) {
        printf("The most significant set bit is at position: %d\n", result);
    } else {
        printf("No set bits found.\n");
    }
    return 0;
}