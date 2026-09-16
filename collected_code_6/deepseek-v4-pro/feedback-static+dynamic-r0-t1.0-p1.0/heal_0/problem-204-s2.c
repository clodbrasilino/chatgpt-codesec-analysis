#include <stdio.h>

int count_character(const char *str, char ch) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    while (*str != '\0') {
        if (*str == ch) {
            count++;
        }
        str++;
    }
    return count;
}

int main(void) {
    const char *text = "hello world";
    char target = 'o';
    int result = count_character(text, target);
    printf("Character '%c' occurs %d times in \"%s\"\n", target, result, text);
    return 0;
}