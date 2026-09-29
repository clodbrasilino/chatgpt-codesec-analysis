#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isInteger(char* str) {
    int length = strlen(str);
    for(int i = 0; i < length; i++) {
        if(i == 0 && (str[i] == '+' || str[i] == '-')) {
            continue;
        }
        if(!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char str1[] = "1234";
    char str2[] = "-1234";
    char str3[] = "1234.56";
    char str4[] = "1234abc";

    printf("%s: %s\n", str1, isInteger(str1) ? "True" : "False");
    printf("%s: %s\n", str2, isInteger(str2) ? "True" : "False");
    printf("%s: %s\n", str3, isInteger(str3) ? "True" : "False");
    printf("%s: %s\n", str4, isInteger(str4) ? "True" : "False");

    return 0;
}