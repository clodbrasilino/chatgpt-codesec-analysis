#include <stdio.h>

int isOdd(int num) {
    return num & 1;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if(isOdd(num)) {
        printf("%d is odd.\n", num);
    } else {
        printf("%d is not odd.\n", num);
    }

    return 0;
}