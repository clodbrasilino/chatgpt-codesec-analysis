#include <stdio.h>

int setRightmostUnsetBit(int n) {
    return n | (n + 1);
}

int main(void) {
    printf("%d\n", setRightmostUnsetBit(5));
    printf("%d\n", setRightmostUnsetBit(13));
    printf("%d\n", setRightmostUnsetBit(14));
    return 0;
}