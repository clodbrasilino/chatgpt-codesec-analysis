#include <stdio.h> 

unsigned int countUnsetBits(unsigned int n) { 
   unsigned int count = 0; 
   while(n) { 
      count += n & 1;
      n >>= 1; 
   } 
   return 32 - count;
}

int main() {
   unsigned int n = 23; 
   printf("%u", countUnsetBits(n)); 
   return 0; 
}