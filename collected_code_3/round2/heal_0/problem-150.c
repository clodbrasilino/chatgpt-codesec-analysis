#include <stdio.h>
#include <stdbool.h>

bool isInfiniteSequence(int num) {
    while(num % 2 == 0 && num != 0) {
        num = num / 2;
    }
    if(num == 1) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(isInfiniteSequence(num)) {
        printf("The number is present in the infinite sequence.\n");
    } else {
        printf("The number is not present in the infinite sequence.\n");
    }
    return 0;
}