#include <stdio.h>

int isOdd(int num) {
    int mask = 1;
    return (num & mask);
}

int main() {
    int num = 0;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (isOdd(num)) {
        printf("%d is an odd number.\n", num);
    } else {
        printf("%d is not an odd number.\n", num);
    }
    return 0;
}