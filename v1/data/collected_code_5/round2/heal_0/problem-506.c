#include<stdio.h>

int permutationCoeff(int n, int k)
{
    if(n == 0 || k == 0){
        return 0;
    }

    if(k > n){
        return 0;
    }
    
    int fact[n + 1];

    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = i*fact[i - 1];

    return fact[n] / fact[n - k];
}

int main()
{
    int n = 10, k = 2;
    int result = permutationCoeff(n, k);
    printf("Permutation coefficient is %d ", result);
    return 0;
}