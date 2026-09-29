#include <stdio.h>

int isAbundant(int num) {
    int sum = 0;
    
    for (int i = 1; i <= num/2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    
    if (sum > num) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    
    if (isAbundant(num)) {
        printf("%d is an abundant number.", num);
    }
    else {
        printf("%d is not an abundant number.", num);
    }
    
    return 0;
}