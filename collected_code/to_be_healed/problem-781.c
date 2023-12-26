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
        return 0; // even count
    }
    else{
        return 1; // odd count
    }
}

int main(){
    int num;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num' is initialized [premium-bughuntingUninit]
     */
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