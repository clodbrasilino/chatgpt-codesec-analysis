#include<stdio.h>

int countVowels(char *str) {
  int count = 0;
  
  /* Possible weaknesses found:
   *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
   */
  for(int i=0; str[i]!='\0'; i++) {
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if(str[i]=='a' || str[i]=='e' || str[i]=='i' || str[i]=='o' || str[i]=='u' || 
       /* Possible weaknesses found:
        *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
        */
       str[i]=='A' || str[i]=='E' || str[i]=='I' || str[i]=='O' || str[i]=='U') {
      count++;
    }
  }
  
  return count;
}

void main() {
  /* Possible weaknesses found:
   *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
   */
  char str[100];
  
  printf("Enter a string: ");
  /* Possible weaknesses found:
   *  Cannot determine that 'str[0]' is initialized [premium-bughuntingUninit]
   *   Does not check for buffer overflows (CWE-120, CWE-20). Use fgets() instead.
   */
  gets(str);
  
  int vowels = countVowels(str);
  
  printf("Number of vowels: %d", vowels);
}