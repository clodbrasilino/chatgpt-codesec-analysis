#include <stdio.h>
#include <string.h>
#define ASCII_SIZE 256

char minChar; 
   
void getMinCharForShortestLength(char* str) 
{ 
    int count[ASCII_SIZE] = {0}; 
    int l = strlen(str); 
    int min = l, i; 
  
    for (i = 0; str[i]; i++) 
        count[str[i]]++; 

    for (i = 0; i < ASCII_SIZE; i++) 
        if (count[i] < min) { 
            min = count[i]; 
            minChar = i; 
        } 
} 

char* removeMinChar(char* str) 
{ 
    getMinCharForShortestLength(str); 
    int i = 0, j = 0; 
    while (*(str + i)) 
    { 
        if(*(str + i) != minChar) 
        { 
            *(str + j) = *(str + i); 
            j++; 
        } 
        i++; 
    } 
      
    return str; 
} 

int main() 
{ 
    char str[] = "test string"; 
    printf("%s", removeMinChar(str)); 
    return 0; 
} 