#include <ctype.h>
#include <stdio.h>
#include <string.h>

void remove_uppercase(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (!isupper(str[i]) || str[i] == ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[] = "Hello World! This is a Test String.";
    printf("Original string: %s\n", str);
    remove_uppercase(str);
    printf("Modified string: %s\n", str);
    return 0;
}