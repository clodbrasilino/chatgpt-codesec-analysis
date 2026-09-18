#include <stdio.h>
#include <stdbool.h>

bool isLucid(int num) {
    int temp, digit;

    temp = num;
    while(temp != 0) {
        digit = temp % 10;
        if(digit != 0 && num % digit == 0) {
            return false;
        }
        temp = temp / 10;
    }

    return true;
}

int getLucid(int n) {
    for(int i = n; i > 0; i--) {
        if(isLucid(i)) {
            return i;
        }
    }
    
    return -1;
}

int main() {
    int num , lucid_number;
    printf("Enter a number: ");
    scanf("%d",&num);
    
    lucid_number = getLucid(num);
    if(lucid_number != -1){
        printf("Lucid number: %d\n", lucid_number);
    }
    else{
        printf("No Lucid number found.\n");
    }

    return 0;
}