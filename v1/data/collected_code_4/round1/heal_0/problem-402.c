#include <stdio.h>

#define ll long long

const int p = 1e9+7;

ll power(ll a, ll n)
{
    ll result=1;
    while(n>0)
    {
        if(n%2) result = (result*a)%p;
        a = (a*a)%p;
        n /= 2;
    }
    return result;
}

ll inverse(ll n)
{
    return power(n, p-2);
}

ll computeNCR(ll n, ll r)
{
    ll numerator = 1;
    ll denominator = 1;
    for(ll i=0; i<r; i++)
    {
        numerator = (numerator*(n-i))%p;
        denominator = (denominator*(i+1))%p;
    }
    return (numerator*inverse(denominator))%p;
}

int main()
{
    ll n, r;
    printf("Enter n and r for the computation of nCr:\n");
    scanf("%lld %lld", &n, &r);
    if(r>n)
    {
        printf("r cannot be greater than n\n");
    }
    else
    {
        printf("The value of nCr is: %lld\n", computeNCR(n, r));
    }
    return 0;
}