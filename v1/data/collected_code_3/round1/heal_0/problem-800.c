#include <stdio.h>
#include <string.h>

void removeSpaces(char* str) 
{ 
    int count = 0;
    for (int i = 0; str[i]; i++) 
        if (str[i] != ' ') 
            str[count++] = str[i]; 
    str[count] = '\0'; 
} 

int main() 
{ 
    char str[] = "C o d e   G e n e r a t o r"; 
    removeSpaces(str); 
    printf("%s", str); 
    return 0; 
} 