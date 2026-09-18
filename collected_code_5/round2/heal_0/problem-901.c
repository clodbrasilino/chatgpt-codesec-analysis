#include <stdio.h>

unsigned int gcd(unsigned int a, unsigned int b){
    if(b == 0)
        return a;
    return gcd(b, a % b);
} 

unsigned int lcm(unsigned int a, unsigned int b){
    return (a * b) / gcd(a, b);
} 

unsigned int findSmallestMultiple(unsigned int n){
    unsigned int ans = 1;
    for (unsigned int i = 1; i <= n; i++)
        ans = lcm(ans, i);
    return ans;
} 

int main() {
    unsigned int n;
    printf("Enter a number: ");
    scanf("%u", &n);
    printf("The smallest multiple is: %u", findSmallestMultiple(n));
    return 0;
}