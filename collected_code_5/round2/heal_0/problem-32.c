#include <stdio.h>
#include <math.h>

int isPrime(long long n)
{
  if(n <= 1) return 0;
  if(n <= 3) return 1;
  
  if(n % 2 == 0 || n % 3 == 0) return 0;
  
  for(long long i = 5; i * i <= n; i += 6)
  {
    if(n % i == 0 || n % (i + 2) == 0) 
    {
      return 0;
    }
  }
  
  return 1;
}

long long largestPrimeFactor(long long n)
{
  long long largestPrime = -1;
  
  for(int i = 2; i <= sqrt(n); i++)
  {
    if(n % i == 0)
    {
      if(isPrime(i))
      {
        largestPrime = (largestPrime < i) ? i : largestPrime;
      }
    }
  }
  
  if(largestPrime == -1)
  {
    return n;
  }
  
  return largestPrime;
}

int main() 
{
  long long n = 315;
  printf("Largest prime factor of %lld is %lld", n, largestPrimeFactor(n));
  
  return 0;
}