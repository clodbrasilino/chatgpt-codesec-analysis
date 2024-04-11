#include <stdio.h>
#include <ctype.h>

int count_uppercase_chars(char* str) {
    int count = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        if(isupper(str[i])) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "Hello World!";
    int count = count_uppercase_chars(str);
    printf("The string '%s' contains %d uppercase characters.\n", str, count);
    return 0;
}