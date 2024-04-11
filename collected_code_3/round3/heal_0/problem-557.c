#include <stdio.h>
#include <ctype.h>

void toggleCase(char *str) {
    int i = 0;
    while(str[i]) {
        if(islower(str[i])) {
            str[i] = toupper(str[i]);
        } else if(isupper(str[i])) {
            str[i] = tolower(str[i]);
        }
        i++;
    }
}

int main() {
    char str[] = "Hello World!";
    toggleCase(str);
    printf("%s\n", str);
    return 0;
}