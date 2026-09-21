#include <stdio.h>
#include <string.h>

void remove_char_occurrences(char *str, char c) {
    if (str == NULL) return;
    char *write = str, *read = str;
    while (*read != '\0') {
        if (*read != c) {
            *write = *read;
            write++;
        }
        read++;
    }
    *write = '\0';
}

int main() {
    char str[] = "programming";
    char c = 'm';
    remove_char_occurrences(str, c);
    printf("%s\n", str);
    return 0;
}