#include <stdio.h>

unsigned long long factorial(int n, int p) {
    unsigned long long fact = 1;
    for(int i = 2; i <= n; i++) {
        fact *= i;
        fact %= p;
    }
    return fact;
}

unsigned long long power(unsigned long long a, int b, int p) {
    unsigned long long res = 1;
    while(b > 0) {
        if(b & 1) {
            res*= a;
            res%= p;
        }
        a*= a;
        a%= p;
        b>>= 1;
    }
    return res;
}

unsigned long long ncrModp(int n, int r, int p) {
    if (r>n)
        return 0;
    unsigned long long fact_n = factorial(n, p);
    unsigned long long fact_r = factorial(r, p);
    /* Possible weaknesses found:
     *  Value stored to 'fact_nr' during its initialization is never read [deadcode.DeadStores]
     */
    unsigned long long fact_nr= factorial(n-r, p);
    return (fact_n * power(fact_r*p, p-2, p)) % p;
}

int main() {
    int n, r, p;
    unsigned long long res;
    printf("Enter values for n, r, and p: \n");
    if(scanf("%d %d %d", &n, &r, &p) != 3) {
       printf("Invalid Inputs\n");
       return 0;
    }
    res = ncrModp(n, r, p);
    printf("The value of %dC%d mod %d is: %llu\n",n, r, p, res);
    return 0;
}