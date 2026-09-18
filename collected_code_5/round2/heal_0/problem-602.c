#include <stdio.h>
#define NO_OF_CHARS 256

char firstRepeat(char *str) {
    int count[NO_OF_CHARS] = {0};
    int index = 0; 
   
    while (*(str + index)) {
        if (count[*(str + index)] == 1)
            return *(str + index);
        count[*(str + index)]++;
        index++;
    }

    return '\0';
}

int main() {
    char str[] = "hello";
    
    char res = firstRepeat(str);
    if(res != '\0')
        printf("The first repeating character is %c", res);
    else
        printf("There are no repeating characters");

    return 0;
}