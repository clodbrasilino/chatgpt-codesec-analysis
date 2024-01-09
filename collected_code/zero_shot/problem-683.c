#include <stdio.h>

int checkSumOfSquares(int num) {
    for (int i = 0; i * i <= num/2; i++) {
        int temp = num - i * i;
        int j = 1;
        
        while (j * j <= temp) {
            if (temp == (j * j)) {
                return 1;
            }
            else {
                j++;
            }
        }
    }
    
    return 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    
    if (checkSumOfSquares(num)) {
        printf("%d can be represented as the sum of two squares.", num);
    }
    else {
        printf("%d cannot be represented as the sum of two squares.", num);
    }
    
    return 0;
}