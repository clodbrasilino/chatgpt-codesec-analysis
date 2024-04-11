#include <stdio.h>

int checkEven(int num) {
    return !(num & 1);
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if(checkEven(num)) {
        printf("%d is even.\n", num);
    } else {
        printf("%d is odd.\n", num);
    }

    return 0;
}