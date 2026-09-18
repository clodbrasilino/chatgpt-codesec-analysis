#include <stdio.h>

unsigned long long gcd(unsigned long long a, unsigned long long b){
    if(b==0) return a;
    return gcd(b, a%b);
}

unsigned long long findSmallestMultiple(int n){
    unsigned long long res = 1;
    for(int i=2; i<=n; i++){
        res = (i*res)/gcd(i, res);
    }
    return res;
}

int main(){
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Smallest multiple of first %d numbers is %llu\n", n, findSmallestMultiple(n));
    return 0;
}