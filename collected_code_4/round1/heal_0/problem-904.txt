#include <stdio.h>
#include <stdbool.h>

bool isEven(int num) {
    return (num % 2 == 0 ? true : false);
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(isEven(num)) {
        printf("Number is even\n");
    } else {
        printf("Number is odd\n");
    }
    return 0;
}