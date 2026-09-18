#include<stdio.h> 
#include<stdlib.h> 

int min(int a, int b); 

int binomialCoeff(int n, int k) 
{ 
    int* C = (int*)malloc((k+1) * sizeof(int)); 
    int i, j, res = 0; 
  
    C[0] = 1; 
  
    for(i = 1; i <= n; i++) 
    { 
        for(j = min(i, k); j > 0; j--) 
            C[j] = C[j] + C[j-1];  
    } 
  
    for(i = 0; i <= k; i+=2) 
        res += C[i]; 
    free(C); 
    return res; 
} 
 
int min(int a, int b) 
{ 
    return (a<b)? a: b;  
} 

int main() 
{ 
    int n = 5; 
    printf("Sum of even index binomial coefficients is %d ",binomialCoeff(n,n)); 
    return 0; 
} 