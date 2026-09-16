#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* minimize_string_length(char *str, char ch) {
    int i, j = 0, len;
    len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] != ch) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
    return str;
}

int main() {
    char str[] = "example character";
    char ch = 'a';
    char* result = minimize_string_length(str, ch);
    printf("%s\n", result);
    return 0;
}