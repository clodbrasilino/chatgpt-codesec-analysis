#include <stdio.h>
#include <string.h>

void removeSpaces(char *str) 
{ 
    int count = 0;
    int i;

    for (i = 0; str[i]; i++) {
        if (str[i] != ' ') 
            str[count++] = str[i];
    }

    str[count] = '\0'; 
} 

int main() 
{
   char str[100];

   printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0';

   removeSpaces(str); 

   printf("\nOutput String :%s", str); 

   return 0;
}