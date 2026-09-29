#include <stdio.h>

int isEven(int num) {
    return !(num & 1);
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if(isEven(num)) {
        printf("%d is even\n", num);
    } else {
        printf("%d is odd\n", num);
    }

    return 0;
}