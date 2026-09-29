#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void reverse_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        reverse_string(strings[i]);
    }
}

int main(void) {
    char *strings[] = {
        "hello",
        "world",
        "example",
        "test",
        NULL
    };
    
    size_t count = 0;
    while (strings[count] != NULL) {
        count++;
    }
    
    reverse_strings(strings, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }
    
    return 0;
}