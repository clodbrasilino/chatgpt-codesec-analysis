#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_hex_even(const char *hex_str);

int is_hex_even(const char *hex_str) {
    if (hex_str == NULL || *hex_str == '\0') {
        return -1;
    }

    size_t start = 0;
    if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        start = 2;
    }

    if (hex_str[start] == '\0') {
        return -1;
    }

    char last_char = '\0';
    for (size_t i = start; hex_str[i] != '\0'; i++) {
        if (!isxdigit((unsigned char)hex_str[i])) {
            return -1;
        }
        last_char = (char)tolower((unsigned char)hex_str[i]);
    }

    if (last_char == '0' || last_char == '2' || last_char == '4' || 
        last_char == '6' || last_char == '8' || last_char == 'a' || 
        last_char == 'c' || last_char == 'e') {
        return 1;
    }

    return 0;
}

int main(void) {
    size_t capacity = 256;
    const size_t max_capacity = 1048576;
    char *buffer = (char *)malloc(capacity);
    
    if (buffer == NULL) {
        return 1;
    }

    size_t length = 0;

    while (fgets(buffer + length, (int)(capacity - length), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length += strlen(buffer + length);
        
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
            length--;
            break;
        }
        
        if (length + 1 >= capacity) {
            if (capacity >= max_capacity) {
                free(buffer);
                return 1;
            }
            
            size_t new_capacity = capacity * 2;
            if (new_capacity < capacity || new_capacity > max_capacity) {
                new_capacity = max_capacity;
            }
            
            char *new_buffer = (char *)realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 1;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
    }

    if (length == 0) {
        free(buffer);
        return 1;
    }

    int result = is_hex_even(buffer);
    
    free(buffer);

    if (result == 1) {
        printf("Even\n");
    } else if (result == 0) {
        printf("Odd\n");
    } else {
        printf("Invalid\n");
        return 1;
    }

    return 0;
}