#include <stdio.h>
#include <stdbool.h>

bool checkPowerOfTwo(int num) {
    if(num && !(num & (num - 1)))
        return true;
    else
        return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(checkPowerOfTwo(num))
        printf("The number can be represented as sum of non-zero powers of 2\n");
    else
        printf("The number cannot be represented as sum of non-zero powers of 2\n");
    return 0;
}