#include <stdio.h>

int check_even(int num) {
    return !(num & 1);
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(check_even(num)) {
        printf("%d is an even number.\n", num);
    } else {
        printf("%d is not an even number.\n", num);
    }
    return 0;
}