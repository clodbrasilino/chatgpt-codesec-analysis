#include <stdio.h>
#include <ctype.h>
#include <string.h>

void capitalize_first_last(char *str) {
    int i = 0;
    int len = strlen(str);

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }
        if (i >= len) break;

        int start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
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