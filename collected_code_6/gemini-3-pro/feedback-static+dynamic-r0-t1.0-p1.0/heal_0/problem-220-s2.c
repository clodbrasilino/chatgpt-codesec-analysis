#include <stdio.h>
#include <string.h>

void replace_chars(char *str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }

    int count = 0;
    while (*str != '\0' && count < n) {
        if (*str == ' ' || *str == ',' || *str == '.') {
            *str = ':';
            count++;
        }
        str++;
    }
}

int main(void) {
    char text1[] = "Hello, world. How are you doing today?";
    replace_chars(text1, 3);
    printf("%s\n", text1);

    char text2[] = "a.b,c d.e,f";
    replace_chars(text2, 10);
    printf("%s\n", text2);

    char text3[] = "NoSpacesHere";
    replace_chars(text3, 5);
    printf("%s\n", text3);

    return 0;
}