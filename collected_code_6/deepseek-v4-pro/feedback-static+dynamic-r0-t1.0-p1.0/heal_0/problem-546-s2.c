#include <stdio.h>
#include <string.h>

char *find_last_occurrence(const char *str, char ch) {
    const char *last = NULL;
    while (*str) {
        if (*str == ch) {
            last = str;
        }
        str++;
    }
    if (ch == '\0') {
        return (char *)str;
    }
    return (char *)last;
}

int main(void) {
    const char *text = "hello world, hello universe";
    char target = 'o';
    char *result = find_last_occurrence(text, target);
    
    if (result != NULL) {
        printf("Last occurrence of '%c' at position: %ld\n", target, result - text);
        printf("Remaining string: %s\n", result);
    } else {
        printf("Character '%c' not found in string\n", target);
    }
    
    return 0;
}