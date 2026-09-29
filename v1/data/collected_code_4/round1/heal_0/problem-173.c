#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_non_alphanumeric(char* str) {
    int len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isalnum((unsigned char)str[i])) {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

int main() {
    char str[] = "H@@ll0, W0r!d!!!";
    remove_non_alphanumeric(str);
    printf("%s", str);
    return 0;
}