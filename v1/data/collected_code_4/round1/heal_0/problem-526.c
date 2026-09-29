#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

void capitalizeFirstLastWord(char *str)
{
    bool capNext = true;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ') {
            capNext = true;
            str[i - 1] = toupper(str[i - 1]);
        }
        else if (capNext) {
            str[i] = toupper(str[i]);
            capNext = false;
        }
    }
    
    str[strlen(str) - 1] = toupper(str[strlen(str) - 1]);
}

int main() 
{
    char str[] = "hello world, i am a developer";
    capitalizeFirstLastWord(str);
    printf("%s\n", str);
    return 0;
}