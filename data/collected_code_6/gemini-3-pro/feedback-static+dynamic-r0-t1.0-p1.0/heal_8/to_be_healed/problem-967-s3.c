#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

bool has_all_vowels(const char *str) {
    if (str == NULL) {
        return false;
    }

    uint8_t vowels = 0;

    for (size_t i = 0; str[i] != '\0'; ++i) {
        char ch = (char)tolower((unsigned char)str[i]);
        if (ch == 'a') vowels |= 1;
        else if (ch == 'e') vowels |= 2;
        else if (ch == 'i') vowels |= 4;
        else if (ch == 'o') vowels |= 8;
        else if (ch == 'u') vowels |= 16;
        
        if (vowels == 31) {
            return true;
        }
    }

    return false;
}

int main(void) {
    size_t capacity = 256;
    size_t len = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return EXIT_FAILURE;
    }
    
    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            break;
        }
        
        if (len + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return EXIT_FAILURE;
            }
            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return EXIT_FAILURE;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        
        buffer[len++] = (char)ch;
    }
    buffer[len] = '\0';

    if (len == 0 && feof(stdin)) {
        printf("Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (has_all_vowels(buffer)) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }

    free(buffer);
    return EXIT_SUCCESS;
}