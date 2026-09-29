#include <stdio.h>
#include <math.h>

int rightmostSetBit(int n){
    if (n == 0) {
        return -1;
    }
    return log2(n & -n) + 1;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int position = rightmostSetBit(n);
    if (position == -1) {
        printf("There are no set bits in the number.\n");
    } else {
        printf("The position of the rightmost set bit in the number is %d.\n", position);
    }

    return 0;
}