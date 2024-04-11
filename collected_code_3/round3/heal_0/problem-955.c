#include <stdio.h>

int isAbundant(int num) {
    int sum = 1;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            if (i * i != num)
                sum = sum + i + num / i;
            else
                sum = sum + i;
        }
    }
    if (sum > num)
        return 1;
    else
        return 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (isAbundant(num))
        printf("%d is an abundant number.\n", num);
    else
        printf("%d is not an abundant number.\n", num);
    return 0;
}