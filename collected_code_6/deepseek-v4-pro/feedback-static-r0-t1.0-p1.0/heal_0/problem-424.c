#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char get_last_char(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return '\0';
    }
    return str[strlen(str) - 1];
}

void extract_last_chars(char **strings, size_t count, char *result) {
    if (strings == NULL || result == NULL || count == 0) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        result[i] = get_last_char(strings[i]);
    }
}

int main(void) {
    char *strings[] = {
        "hello",
        "world",
        "C",
        "programming",
        ""
    };
    
    size_t count = sizeof(strings) / sizeof(strings[0]);
    char *last_chars = (char *)malloc(count * sizeof(char));
    
    if (last_chars == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    extract_last_chars(strings, count, last_chars);
    
    for (size_t i = 0; i < count; i++) {
        if (last_chars[i] == '\0') {
            printf("String %zu: (empty)\n", i);
        } else {
            printf("String %zu: %c\n", i, last_chars[i]);
        }
    }
    
    free(last_chars);
    return 0;
}