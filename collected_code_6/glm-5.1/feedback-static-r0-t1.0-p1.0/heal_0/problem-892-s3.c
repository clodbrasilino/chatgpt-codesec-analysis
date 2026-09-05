#include <stdio.h>
#include <string.h>

void remove_multiple_spaces(char *str) {
    if (str == NULL) {
        return;
    }

    char *dst = str;
    char *src = str;
    int is_space = 0;

    while (*src != '\0') {
        if (*src == ' ') {
            if (!is_space) {
                *dst++ = *src;
                is_space = 1;
            }
        } else {
            *dst++ = *src;
            is_space = 0;
        }
        src++;
    }

    *dst = '\0';
}

int main(int argc, char *argv[]) {
    char str[] = "This  is   a    string     with     multiple    spaces.";

    printf("Original: \"%s\"\n", str);
    remove_multiple_spaces(str);
    printf("Modified: \"%s\"\n", str);

    return 0;
}