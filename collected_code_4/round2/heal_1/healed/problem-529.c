#include<stdio.h>

long long findNthJacobsthalLucas(int n);

int main() {
    int n;
    long long result;

    printf("Enter a number: ");
    scanf("%d", &n);

    if(n < 0) {
        printf("Error: Input should be a non-negative number.\n");
        return 1;
    }

    result = findNthJacobsthalLucas(n);
    printf("The %dth Jacobsthal-Lucas number is: %lld\n", n, result);

    return 0;
}
  
long long findNthJacobsthalLucas(int n) {
    long long j0 = 2, j1 = 1;

    if (n==0) 
        return j0;
    
    if (n==1) 
        return j1;

    for(int i = 2; i <= n; i++) {
        long long jn = 2 * j0 + j1;
        j0 = j1;
        j1 = jn;
        if(i == n)
            return jn;
    }

    return 0;
}