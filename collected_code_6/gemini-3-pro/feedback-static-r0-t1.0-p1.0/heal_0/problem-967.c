#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        str++;
    }

    return found_a && found_e && found_i && found_o && found_u;
}

int main(void) {
    char buffer[256];

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (contains_all_vowels(buffer)) {
            printf("The string contains all vowels.\n");
        } else {
            printf("The string does not contain all vowels.\n");
        }
    } else {
        printf("Error reading input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}