#include <stdio.h>
#include <string.h>

int count_occurrences(char *str, char c) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "Hello, World!";
    char c = 'l';
    printf("Number of occurrences of '%c' in '%s': %d\n", c, str, count_occurrences(str, c));
    return 0;
}