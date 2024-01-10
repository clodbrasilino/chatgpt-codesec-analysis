#include <stdio.h>

int isAbundant(int num) {
    int sum = 0;

    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }

    return sum > num;
}

int main() {
    int number = 0;
    
    printf("Enter a number: ");
    scanf("%d", &number);

    if (isAbundant(number)) {
        printf("%d is an abundant number.\n", number);
    } else {
        printf("%d is not an abundant number.\n", number);
    }

    return 0;
}