#include <stdio.h>

int factorial(int n){
    if(n <= 1)
        return 1;
    return n * factorial(n-1);
}

int permutationCoefficient(int n, int k){
    return factorial(n) / factorial(n-k);
}

int main(){
    int n, k;
    printf("Enter value of n and k: ");
    scanf("%d %d", &n, &k);
    printf("Permutation coefficient of p(%d, %d) is %d", n, k, permutationCoefficient(n, k));
    return 0;
}