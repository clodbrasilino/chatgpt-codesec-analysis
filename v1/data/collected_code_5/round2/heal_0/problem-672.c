#include <stdio.h>

int findMax(int num1, int num2, int num3) {
    int max;
    
    if(num1 > num2) {
        if(num1 > num3) {
            max = num1;
        } else {
            max = num3;
        }
    } else {
        if(num2 > num3) {
            max = num2;
        } else {
            max = num3;
        }
    }
   
    return max;
}

int main() {
    int num1, num2, num3;
    printf("Enter three numbers: ");
    scanf("%d %d %d", &num1, &num2, &num3);

    printf("Max number : %d", findMax(num1, num2, num3));

    return 0;
}