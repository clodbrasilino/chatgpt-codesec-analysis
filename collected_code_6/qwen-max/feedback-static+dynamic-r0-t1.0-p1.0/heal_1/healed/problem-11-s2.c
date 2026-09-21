#include <stdio.h>
#include <string.h>

void remove_char_occurrences(char *str, char c) {
    int length = 0;
    while (str[length] != '\0') length++;
    int first = -1, last = -1;
    for (int i = 0; i < length; i++) {
        if (str[i] == c) {
            if (first == -1) first = i;
            last = i;
        }
    }
    if (first != -1) {
        memmove(&str[first], &str[first + 1], length - first - 1);
        if (last != first) { 
            last--; 
        }
        memmove(&str[last], &str[last + 1], length - last - 1);
    }
}

int main() {
    char str[] = "programming";
    char c = 'm';
    remove_char_occurrences(str, c);
    printf("%s\n", str);
    return 0;
}