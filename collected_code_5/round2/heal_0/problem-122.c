#include <stdio.h>
#include <math.h>

int IsSmartNumber(int num){
    int val = (int)sqrt(num);
    return ((val*val) == num);
}

int NthSmartNumber(int n){
    int count = 0;
    for(int num = 1;; num++){
        if (IsSmartNumber(num)){
            count++;
            if (count == n){
                return num;
            }
        }
    }
    return -1; // To handle unexpected n values (more than total no. of smart numbers)
}

int main(){

    int n;

    printf("Enter the nth position: ");
    scanf("%d", &n);

    if(n <= 0){
        printf("Invalid input. Please enter a positive number.\n");
        return 1;
    }

    int result = NthSmartNumber(n);

    if(result == -1){
        printf("No smart number found at given position.\n");
        return 1;
    }

    printf("The %dth smart number is: %d\n", n, result);

    return 0;
}