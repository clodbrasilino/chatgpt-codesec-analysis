#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_words(char *str) {
    char *start, *end, temp;
    int len = 0;
    while (str[len] != '\0') len++;
    for (start = end = str; start <= str + len && *start; start++) {
        if (*start == ' ' || *(start + 1) == '\0') {
            if (*(start + 1) == '\0') start++;
            start--;
            while (end < start) {
                temp = *end;
                *end = *start;
                *start = temp;
                end++;
                start--;
            }
            end = start + 2;
        }
    }
}

int main() {
    char str[] = "Hello World This is C";
    reverse_words(str);
    printf("%s\n", str);
    return 0;
}