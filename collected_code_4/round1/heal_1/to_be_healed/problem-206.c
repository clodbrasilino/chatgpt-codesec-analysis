#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1024

void concatenate_tuples(char (*arr)[10], int size, char (*result)[20]) { 
   for(int i = 0; i < size - 1; ++i) {
      strncpy(result[i], arr[i], 10);
      strncat(result[i], arr[i + 1], 10);
   }
   result[size - 1][0] = '\0';
}

int main(){
   /* Possible weaknesses found:
    *  initializer-string for array of 'char' is too long
    *  (near initialization for 'arr[8]')
    */
   char arr[10][10] = {"Apple", "Banana", "Cherry", "Date", "Elderberry", "Fig", "Grape", "Honeydew", "IndianPrune", "Jackfruit"};
   char result[MAX_SIZE][20];
   concatenate_tuples(arr, 10, result);
   for(int i = 0; i < 10 - 1; ++i)
      printf("%s\n", result[i]);
   return 0;
}