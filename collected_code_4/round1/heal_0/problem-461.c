#include <stdio.h>
#include <ctype.h>

int count_uppercase_chars(char *str) {
    int count = 0;
    if(str == NULL) 
        return count;

    for(int i = 0; str[i]; i++) {
        if(isupper(str[i])) 
            count++;
    }
    return count;
}

int main() {
    char str[] = "Hello, Please Count The UpperCase Characters.";
    int count = count_uppercase_chars(str);

    printf("Number of uppercase characters in the given string: %d\n", count);

    return 0;
}