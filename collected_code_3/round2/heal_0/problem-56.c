#include <stdio.h>

int reverse(int num) {
    int rev = 0;
    while(num != 0) {
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    return rev;
}

int isOneLessThanTwiceReverse(int num) {
    int rev = reverse(num);
    if(num == 2 * rev - 1) {
        return 1;
    }
    return 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(isOneLessThanTwiceReverse(num)) {
        printf("The number is one less than twice its reverse.\n");
    } else {
        printf("The number is not one less than twice its reverse.\n");
    }
    return 0;
}