#include<stdio.h>

int findAsciiValue(char ch){
    return (int)ch;
}

int main() {
  char ch;
  printf("Enter a character: ");
  scanf("%c", &ch);
  
  int asciiVal = findAsciiValue(ch);

  printf("The ASCII value of %c = %d\n", ch, asciiVal);
  
  return 0;
}