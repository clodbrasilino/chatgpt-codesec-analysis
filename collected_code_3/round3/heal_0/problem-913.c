#include <stdio.h>
#include <string.h>
#include <ctype.h>

int checkNumberAtEnd(char* str) {
    int len = strlen(str);
    if(isdigit(str[len - 1]))
        return 1;
    else
        return 0;
}

int main() {
    char str[] = "HelloWorld123";
    int result = checkNumberAtEnd(str);
    if(result == 1)
        printf("Number at the end of the string\n");
    else
        printf("No number at the end of the string\n");
    return 0;
}