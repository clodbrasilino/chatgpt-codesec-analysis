#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumSwapsToConvert(char *a, char *b, int n){
    int count = 0;
    int i;
    for(i = 0; i < n; i++){
      if(a[i] != b[i]){
        count++;
      }
    }
    return count/2;
}

int main(){
    char a[] = "11001";
    char b[] = "10011";
    int n = strlen(a);
    if(n != strlen(b)){
      printf("Strings of unequal length.\n");
      return -1;
    }
    int result = minimumSwapsToConvert(a, b, n);
    printf("Minimum swaps required: %d\n", result);
    return 0;
}   