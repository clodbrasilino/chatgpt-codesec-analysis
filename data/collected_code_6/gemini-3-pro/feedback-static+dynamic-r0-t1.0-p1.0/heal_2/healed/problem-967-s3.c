#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool has_all_vowels(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool found_a = false;
    bool found_e = false;
    bool found_i = false;
    bool found_o = false;
    bool found_u = false;

    for (size_t i = 0; str[i] != '\0'; ++i) {
        char ch = (char)tolower((unsigned char)str[i]);
        if (ch == 'a') found_a = true;
        else if (ch == 'e') found_e = true;
        else if (ch == 'i') found_i = true;
        else if (ch == 'o') found_o = true;
        else if (ch == 'u') found_u = true;
        
        if (found_a && found_e && found_i && found_o && found_u) {
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
    
    buffer[0] = '\0';
    char chunk[256];

    while (fgets(chunk, sizeof(chunk), stdin) != NULL) {
        size_t chunk_len = strlen(chunk);
        
        if (len + chunk_len + 1 > capacity) {
            size_t new_capacity = capacity * 2;
            while (new_capacity < len + chunk_len + 1) {
                new_capacity *= 2;
            }
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return EXIT_FAILURE;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        
        memcpy(buffer + len, chunk, chunk_len + 1);
        len += chunk_len;
        
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
            break;
        }
    }

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