#include <stdio.h>

int isOdd(int num){
   int count=0;
   for(int i=1; i<=num; i++){
      if(num%i == 0){
         count++;
      }
   }
   if(count%2 != 0){
      return 1;
   }
   else{
      return 0;
   }
}

int countOddFactors(int start, int end){
   int count = 0;
   for(int i=start; i<=end; i++){
      if(isOdd(i)){
         count++;
      }
   }
   return count;
}

int main(){
   int start = 0, end = 0;
   printf("Enter the range: \n");
   scanf("%d %d", &start, &end);
   printf("Number of elements with odd factors: %d\n", countOddFactors(start, end));
   return 0;
}