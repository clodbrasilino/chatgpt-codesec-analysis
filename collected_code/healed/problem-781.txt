#include <stdio.h>

int countDivisors(int n){
    int count = 0;
    for(int i=1; i<=n; i++){
        if(n%i == 0){
            count++;
        }
    }
    return count;
}

int checkDivisorCount(int num){
    int divisorCount = countDivisors(num);
    if(divisorCount % 2 == 0){
        return 0; 
    }
    else{
        return 1; 
    }
}

int main(){
    int num = 0;
    printf("Enter a number: ");
    scanf("%d", &num);
    int result = checkDivisorCount(num);
    if(result == 0){
        printf("Even count of divisors\n");
    }
    else{
        printf("Odd count of divisors\n");
    }
    return 0;
}