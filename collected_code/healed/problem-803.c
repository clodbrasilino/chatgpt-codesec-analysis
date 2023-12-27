#include <stdio.h>

int isPerfectSquare(int num) {
    int i;
    for (i = 1; i * i <= num; i++) {
        if (i * i == num) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int number;
    printf("Enter a number: ");
    if(scanf("%d", &number)!=1){
        printf("Failed to read integer.\n");
        return 1;
    }

    if (isPerfectSquare(number)) {
        printf("%d is a perfect square.\n", number);
    } else {
        printf("%d is not a perfect square.\n", number);
    }

    return 0;
}