#include <stdio.h>

char* findLastOccurrence(char* str, char ch) {
    char* last = NULL;

    if (str == NULL) {
        return last;
    }

    while (*str != '\0') {
        if (*str == ch) {
            last = str;
        }
        str++;
    }

    return last;
}

int main() {
    char str[] = "hello";
    char ch = 'l';

    char* lastOccurrence = findLastOccurrence(str, ch);

    if (lastOccurrence != NULL) {
        printf("Last occurrence of '%c' is at index %ld\n", ch, lastOccurrence - str);
    } else {
        printf("Character '%c' not found in string.\n", ch);
    }

    return 0;
}