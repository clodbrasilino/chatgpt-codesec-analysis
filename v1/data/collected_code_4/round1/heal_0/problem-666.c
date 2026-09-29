#include <stdio.h>
#include <string.h>

int count_chars(char* str, char c) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "Hello World";
    char c = 'l';
    int count = count_chars(str, c);
    printf("The character '%c' appeared %d times.\n", c, count);
    return 0;
}