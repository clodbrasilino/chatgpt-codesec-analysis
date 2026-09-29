#include <stdio.h>
#include <string.h>

void remove_char_occurrences(char *str, char c) {
    int length = strlen(str);
    int write_index = 0;

    for (int i = 0; i < length; i++) {
        if (str[i] != c) {
            str[write_index++] = str[i];
        }
    }
    str[write_index] = '\0';
}

int main() {
    char str[] = "programming";
    char c = 'm';
    remove_char_occurrences(str, c);
    printf("%s\n", str);
    return 0;
}