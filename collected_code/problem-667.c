#include<stdio.h>

int countVowels(char *str) {
  int count = 0;
  
  for(int i=0; str[i]!='\0'; i++) {
    if(str[i]=='a' || str[i]=='e' || str[i]=='i' || str[i]=='o' || str[i]=='u' || 
       str[i]=='A' || str[i]=='E' || str[i]=='I' || str[i]=='O' || str[i]=='U') {
      count++;
    }
  }
  
  return count;
}

void main() {
  char str[100];
  
  printf("Enter a string: ");
  gets(str);
  
  int vowels = countVowels(str);
  
  printf("Number of vowels: %d", vowels);
}