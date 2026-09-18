#include <stdio.h>

int reverse(int num) {
    int rev = 0;
    while(num > 0){
        rev = rev * 10 + num % 10;
        num = num / 10;
    }
    return rev;
}

int isOneLessTwiceReverse(int num) {
    int rev = reverse(num);
    return 2 * rev == num + 1;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if(isOneLessTwiceReverse(num))
        printf("%d is one less than twice its reverse\n", num);
    else
        printf("%d is not one less than twice its reverse\n", num);

    return 0;
}