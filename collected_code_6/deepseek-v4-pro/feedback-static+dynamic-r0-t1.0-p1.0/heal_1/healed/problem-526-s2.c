#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalize_first_last(char *str) {
    int i = 0;

    while (str[i] != '\0') {
        while (str[i] != '\0' && isspace((unsigned char)str[i])) {
            i++;
        }
        if (str[i] == '\0') break;

        int start = i;
        while (str[i] != '\0' && !isspace((unsigned char)str[i])) {
            i++;
        }
        int end = i - 1;

        str[start] = toupper((unsigned char)str[start]);
        str[end] = toupper((unsigned char)str[end]);
    }
}

int main(void) {
    char text[] = "hello world from c programming";

    capitalize_first_last(text);
    printf("%s\n", text);

    return 0;
}