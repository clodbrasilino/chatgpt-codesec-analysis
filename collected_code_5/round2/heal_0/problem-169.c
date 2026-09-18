#include <stdio.h>

unsigned long long pellNumber(int n)
{
   unsigned long long pellNumbers[n+1];
   pellNumbers[0] = 0;
   pellNumbers[1] = 1;

   for (int i = 2; i <= n; i++)
   {
      pellNumbers[i] = 2*pellNumbers[i-1] + pellNumbers[i-2];
   }

   return pellNumbers[n];
}

int main()
{
   int n;
   printf("Enter a positive integer: ");
   scanf("%d", &n);

   if (n < 0)
   {
      printf("Input can not be negative. Please enter a positive integer.\n");
      return -1;
   }
   
   printf("Pell number at position %d is: %llu\n",n , pellNumber(n));

   return 0;
}