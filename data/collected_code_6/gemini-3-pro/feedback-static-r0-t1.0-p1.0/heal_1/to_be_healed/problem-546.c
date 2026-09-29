#include <stdio.h>
#include <string.h>

char* find_last_occurrence(const char *str, int c) {
    if (str == NULL) {
        return NULL;
    }

    const char *last_occurrence = NULL;

    while (*str != '\0') {
        if (*str == c) {
            last_occurrence = str;
        }
        str++;
    }

    if (c == '\0') {
        return (char *)str;
    }

    return (char *)last_occurrence;
}

int main() {
    const char *text = "hello world";
    char target = 'l';

    char *result = find_last_occurrence(text, target);

    if (result != NULL) {
        /* Possible weaknesses found:
         *  %ld in format string (no. 2) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'. [invalidPrintfArgType_sint]
         */
        printf("Last occurrence of '%c' found at index: %ld\n", target, result - text);
    } else {
        printf("Character '%c' not found in the string.\n", target);
    }
    
    target = 'z';
    result = find_last_occurrence(text, target);
    
    if (result != NULL) {
        /* Possible weaknesses found:
         *  %ld in format string (no. 2) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'. [invalidPrintfArgType_sint]
         */
        printf("Last occurrence of '%c' found at index: %ld\n", target, result - text);
    } else {
        printf("Character '%c' not found in the string.\n", target);
    }

    return 0;
}