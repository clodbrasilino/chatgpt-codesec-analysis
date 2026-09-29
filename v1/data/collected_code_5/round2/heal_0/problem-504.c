#include <stdio.h>

long long cubeSum(int n) {
    long long sum = 0;
    for(int i=1; i<=n; i++ ) {
        sum = sum + (i*i*i);
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    if(n<=0) {
        printf("Enter a natural number\n");
        return 1;       
    }    
    printf("Cube Sum of first %d natural numbers is: %lld\n", n, cubeSum(n));
    return 0;
}