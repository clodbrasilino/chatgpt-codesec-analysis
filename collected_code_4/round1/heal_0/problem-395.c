#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

char firstNonRepeating(char* str) 
{
    int count[NO_OF_CHARS] = {0};
    int index;
    
    for(index = 0; *(str+index);  index++)
       count[*(str+index)]++;
    
    for(index = 0; *(str+index);  index++)
      if (count[*(str+index)] == 1)
         return *(str+index);
    
    return '\0';
}

int main()
{
    char str[100];
    printf("Enter a string to find its first non-repeating character: ");
    fgets(str, 100, stdin);	// Reading input string from the user.
     
    char res = firstNonRepeating(str);
    
    if(res != '\0')
      printf("The first non-repeating character is  %c", res);
    else
      printf("All characters are repeating or string is empty");
    
    return 0;
}