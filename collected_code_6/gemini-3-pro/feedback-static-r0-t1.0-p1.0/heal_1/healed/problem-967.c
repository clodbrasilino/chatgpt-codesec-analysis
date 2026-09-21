#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool contains_all_vowels(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool found_a = false;
    bool found_e = false;
    bool found_i = false;
    bool found_o = false;
    bool found_u = false;

    while (*str) {
        char ch = tolower((unsigned char)*str);
        if (ch == 'a') found_a = true;
        else if (ch == 'e') found_e = true;
        else if (ch == 'i') found_i = true;
        else if (ch == 'o') found_o = true;
        else if (ch == 'u') found_u = true;
        
        if (found_a && found_e && found_i && found_o && found_u) {
            return true;
        }
        
        str++;
    }

    return false;
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t chars_read;

    printf("Enter a string: ");
    chars_read = getline(&buffer, &bufsize, stdin);

    if (chars_read != -1) {
        if (chars_read > 0 && buffer[chars_read - 1] == '\n') {
            buffer[chars_read - 1] = '\0';
        }

        if (contains_all_vowels(buffer)) {
            printf("The string contains all vowels.\n");
        } else {
            printf("The string does not contain all vowels.\n");
        }
    } else {
        printf("Error reading input.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}