#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* removeDuplicates(char* str) {

    int hash = 0; 
    int currIndex = 0; 
  
    for(int i = 0; str[i]; i++) {

        int temp = 1;
        temp = temp << (str[i] - 'a'); 
        
        if((hash & temp) == 0) {
            str[currIndex++] = str[i];
            hash |= temp;   
        }
    }
    
    str[currIndex] = '\0'; 
    return str;
}

int main() {

    char str[] = "aabbbcc";
    printf("%s\n", removeDuplicates(str));
    return 0;
}