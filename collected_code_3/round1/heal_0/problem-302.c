#include <stdio.h>

unsigned int findMSBSet(unsigned int num) {
    int msb = -1;
    while (num) {
        num = num >> 1;
        msb++;
    }
    return msb;
}

int main() {
    unsigned int num = 18;
    int msb = findMSBSet(num);
    if (msb != -1)
        printf("The most significant set bit is : %d\n", msb);
    else
        printf("No set bit is present\n");
    return 0;
}