#include <stdio.h>
#define MAX 1000000

unsigned long long memo[MAX];

unsigned long long findMaxSum(unsigned int n){
    if(n<MAX && memo[n] != 0)
        return memo[n];
    if(n <= 2)
        return n;
    unsigned long long result = findMaxSum(n/2) + findMaxSum(n/3) + findMaxSum(n/4) + findMaxSum(n/5);
    if(n> result)
        result = n;
    if(n<MAX)
        memo[n] = result;
    return result;
}

int main(){
    unsigned int n;
    printf("Enter the value for n: ");
    scanf("%u", &n);
    printf("Maximum possible sum : %llu\n", findMaxSum(n));
    return 0;
}