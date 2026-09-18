#include<stdio.h>

long long factorial(int n){
    if(n==0)
        return 1;
    else
        return n * factorial(n - 1);
}

long long permutation(int n, int k){
    long long result = 0;
    if(k > n)
        return 0;
    result = factorial(n) / factorial(n-k);
    return result;
}
    
int main() {
    int n, k;
    printf("Enter the total number of elements: ");
    scanf("%d", &n);
    printf("Enter the number of elements to permute: ");
    scanf("%d", &k);
    printf("The permutation of %d and %d is %lld.\n", n, k, permutation(n,k));
    return 0;
}