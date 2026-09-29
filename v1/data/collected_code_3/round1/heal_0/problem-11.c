#include <stdio.h>
#include <string.h>

void remove_char(char* str, char c) {
    int len = strlen(str);
    int first = -1, last = -1;

    for (int i = 0; i < len; i++) {
        if (str[i] == c) {
            if (first == -1)
                first = i;
            last = i;
        }
    }

    if (first != -1) {
        for (int i = first; i < len; i++)
            str[i] = str[i + 1];
        len--;
    }

    if (last != -1) {
        for (int i = last - 1; i < len; i++)
            str[i] = str[i + 1];
    }
}

int main() {
    char str[] = "Hello, World!";
    char c = 'o';

    remove_char(str, c);
    printf("%s\n", str);

    return 0;
}