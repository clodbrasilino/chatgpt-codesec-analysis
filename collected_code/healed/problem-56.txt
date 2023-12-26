#include <stdio.h>

int reverse(int num){
    int rev = 0;
    while(num != 0){
        rev = rev*10 + num%10;
        num /= 10;
    }
    return rev;
}

int isOneLessThanTwiceReverse(int num){
    int rev = reverse(num);
    if(num == (2*rev)-1){
        return 1;
    }
    return 0;
}

int main() {
    int num = 0;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(isOneLessThanTwiceReverse(num)){
        printf("%d is one less than twice its reverse.", num);
    }else{
        printf("%d is not one less than twice its reverse.", num);
    }
    return 0;
}